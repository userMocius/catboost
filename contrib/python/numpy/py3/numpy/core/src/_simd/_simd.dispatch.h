// cache_hash:3674810845
/**
 * AUTOGENERATED DON'T EDIT
 * Please make changes to the code generator (distutils/ccompiler_opt.py)
 */
#ifndef NPY__CPU_DISPATCH_EXPAND_
    #define NPY__CPU_DISPATCH_EXPAND_(X) X
#endif
#undef NPY__CPU_DISPATCH_BASELINE_CALL
#undef NPY__CPU_DISPATCH_CALL
#define NPY__CPU_DISPATCH_BASELINE_CALL(CB, ...) \
	NPY__CPU_DISPATCH_EXPAND_(CB(__VA_ARGS__))
#define NPY__CPU_DISPATCH_CALL(CHK, CB, ...) \
	NPY__CPU_DISPATCH_EXPAND_(CB((CHK(AVX512_SKX)), AVX512_SKX, __VA_ARGS__)) \
	NPY__CPU_DISPATCH_EXPAND_(CB((CHK(AVX512F)), AVX512F, __VA_ARGS__)) \
	NPY__CPU_DISPATCH_EXPAND_(CB((CHK(AVX)&&CHK(F16C)&&CHK(FMA3)&&CHK(AVX2)), FMA3__AVX2, __VA_ARGS__)) \
	NPY__CPU_DISPATCH_EXPAND_(CB((CHK(SSE)&&CHK(SSE2)&&CHK(SSE3)&&CHK(SSSE3)&&CHK(SSE41)&&CHK(POPCNT)&&CHK(SSE42)), SSE42, __VA_ARGS__))
