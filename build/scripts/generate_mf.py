import json
import logging
import optparse
import os
import sys

import process_command_files as pcf

class BadMfError(Exception):
    pass


class GplNotAllowed(Exception):
    pass


def parse_args():
    args = pcf.get_args(sys.argv[1:])
    lics, peers, free_args, credits = [], [], [], []
    current_list = free_args
    for a in args:
        if a == '-Ya,lics':
            current_list = lics
        elif a == '-Ya,peers':
            current_list = peers
        elif a == '-Ya,credits':
            current_list = credits
        elif a and a.startswith('-'):
            current_list = free_args
            current_list.append(a)
        else:
            current_list.append(a)

    parser = optparse.OptionParser()
    parser.add_option('--no-gpl', action='store_true')
    parser.add_option('--allow-lgpl', action='store_true')
    parser.add_option('--build-root')
    parser.add_option('--module-name')
    parser.add_option('-o', '--output')
    parser.add_option('-c', '--credits-output')
    parser.add_option('-t', '--type')
    opts, _ = parser.parse_args(free_args)
    return lics, peers, credits, opts,


def validate_mf(mf, module_type):
    path = mf['path']

    if mf.get('no_gpl', False):
        if module_type == 'LIBRARY':
            raise Exception('Macro [[imp]]NO_GPL[[rst]] not allowed for [[bad]]LIBRARY[[rst]]')

        if 'dependencies' not in mf:
            raise BadMfError("Can't validate manifest for {}: no info about 'dependencies'".format(path))

        bad_mfs = [dep['path'] for dep in mf['dependencies'] if 'licenses' not in dep]
        if bad_mfs:
            raise BadMfError("Can't validate licenses for {}: no 'licenses' info for dependency(es) {}".format(path,', '.join(bad_mfs)))

        lgpl_ok = mf.get('allow_lgpl', False)
        bad_lics = ["[[imp]]{}[[rst]] licensed with {}".format(dep['path'], lic) for dep in mf['dependencies'] for lic in dep['licenses'] if 'gpl' in lic.lower() and (not lgpl_ok or 'lgpl' not in lic.lower())]
        if bad_lics:
            raise GplNotAllowed('[[bad]]License check failed:[[rst]]\n{}'.format('\n'.join(bad_lics)))

        bad_contribs = [dep['path'] + '/ya.make' for dep in mf['dependencies'] if dep['path'].startswith('contrib/') and not dep['licenses']]
        if bad_contribs:
            logging.warning("[[warn]]Can't check NO_GPL properly[[rst]] because the following project(s) has no [[imp]]LICENSE[[rst]] macro:\n%s", '\n'.join(bad_contribs))


def generate_header(meta):
    return '-' * 20 + meta.get('path', 'Unknown module') + '-' * 20


def generate_mf():
    lics, peers, credits, options = parse_args()

    meta = {
        'module_name': options.module_name,
        'path': os.path.dirname(options.output),
        'licenses': lics,
        'dependencies': [],
        'no_gpl': options.no_gpl,
        'allow_lgpl': options.allow_lgpl,
        'license_texts': ''
    }

    build_root = options.build_root
    file_name = os.path.join(build_root, options.output)

    if options.type != 'LIBRARY':
        for rel_filename in peers:
            with open(os.path.join(build_root, rel_filename + '.mf')) as peer_file:
                peer_meta = json.load(peer_file)
                meta['dependencies'].append(peer_meta)

    if credits:
        union_texts = []
        for texts_file in credits:
            with open(texts_file) as f:
                union_texts.append(f.read())
        meta['license_texts'] = '\n\n'.join(union_texts)

    if options.credits_output:
        final_credits = []
        if meta['license_texts']:
            final_credits.append(generate_header(meta) + '\n' + meta['license_texts'])
        for peer in peers:
            candidate = peer + '.mf'
            with open(candidate) as src:
                data = json.loads(src.read())
                texts = data.get('license_texts')
                if texts:
                    final_credits.append(generate_header(data) + '\n' + texts)

        with open(options.credits_output, 'w') as f:
            f.write('\n\n'.join(final_credits))

    with open(file_name, 'w') as mf_file:
        json.dump(meta, mf_file, indent=4)

    validate_mf(meta, options.type)


if __name__ == '__main__':
    try:
        generate_mf()
    except Exception as e:
        sys.stderr.write(str(e) + '\n')
        sys.exit(1)
