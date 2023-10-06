// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// The BSDs have lots of *_l functions.  We don't want to define those symbols
// on other platforms though, for fear of conflicts with user code.  So here,
// we will define the mapping from an internal macro to the real BSD symbol.
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___BSD_LOCALE_DEFAULTS_H
#define _LIBCPP___BSD_LOCALE_DEFAULTS_H

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

#define __libcpp_mb_cur_max_l(loc)                          MB_CUR_MAX_L(loc)
#define __libcpp_btowc_l(ch, loc)                           btowc_l(ch, loc)
#define __libcpp_wctob_l(wch, loc)                          wctob_l(wch, loc)
#define __libcpp_wcsnrtombs_l(dst, src, nwc, len, ps, loc)  wcsnrtombs_l(dst, src, nwc, len, ps, loc)
#define __libcpp_wcrtomb_l(src, wc, ps, loc)                wcrtomb_l(src, wc, ps, loc)
#define __libcpp_mbsnrtowcs_l(dst, src, nms, len, ps, loc)  mbsnrtowcs_l(dst, src, nms, len, ps, loc)
#define __libcpp_mbrtowc_l(pwc, s, n, ps, l)                mbrtowc_l(pwc, s, n, ps, l)
#define __libcpp_mbtowc_l(pwc, pmb, max, l)                 mbtowc_l(pwc, pmb, max, l)
#define __libcpp_mbrlen_l(s, n, ps, l)                      mbrlen_l(s, n, ps, l)
#define __libcpp_localeconv_l(l)                            localeconv_l(l)
#define __libcpp_mbsrtowcs_l(dest, src, len, ps, l)         mbsrtowcs_l(dest, src, len, ps, l)
// Workaround for Visual Studio preprocessor bug - explicitly mention all non-variadic parameters.
#define __libcpp_snprintf_l(__s, __n, __l, __f, ...)        snprintf_l(__s, __n, __l, __f, ##__VA_ARGS__)
#define __libcpp_asprintf_l(__ret, __l, __f, ...)           asprintf_l(__ret, __l, __f, ##__VA_ARGS__)
#define __libcpp_sscanf_l(__s, __l, __f, ...)               sscanf_l(__s, __l, __f, ##__VA_ARGS__)

#endif // _LIBCPP___BSD_LOCALE_DEFAULTS_H
