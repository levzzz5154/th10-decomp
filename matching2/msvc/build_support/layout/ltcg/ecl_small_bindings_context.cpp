// Compiler context only; never selected as recovered game code.
#include "../../../src/script/sptcmd/ecl_reset_variable_bindings.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall EclSmallBindingsCompilerContext(
        EclVm4** resets, int count) {
    while (count--)
        (*resets++)->ResetVariableBindings();
    return 0;
}
#pragma code_seg()
