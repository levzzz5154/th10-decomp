// Compiler context only; never selected as recovered game code.
//
// The lookup implementation is included in the context translation unit, as
// required by the native-LTCG driver contract; the writer is co-compiled from
// its additional source below.
#include "../../../src/script/sptcmd/ecl_find_variable_00450160.cpp"

struct EclScratchVm_004505b0 {
    __declspec(noinline) int WriteScratch(char type, unsigned int size,
                                           const void* source);
};

#pragma code_seg(".text$07context")
int __stdcall EclVariableClusterCompilerContext(
        EclVariableVm_00450160** finders,
        EclScratchVm_004505b0** writers,
        int* variables, const char* types,
        const unsigned int* sizes, const void* const* sources,
        int count) {
    while (count--) {
        (*writers++)->WriteScratch(*types++, *sizes++, *sources++);
        (*finders++)->FindVariable(*variables++);
    }
    return 0;
}
#pragma code_seg()
