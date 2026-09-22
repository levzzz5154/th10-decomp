// Compiler context only; never selected as recovered game code.
#include "../../src/script/ecl_reset_variable_bindings_00450190.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall EclSmallBindingsCompilerContext(
        EclVm_00450190** resets, int count) {
    while (count--)
        (*resets++)->ResetVariableBindings();
    return 0;
}
#pragma code_seg()
