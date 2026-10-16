// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_43a6f0.cpp"

#pragma code_seg(".text$03context")
int __stdcall SwapCompilerContext(unsigned short* values, int count) {
    while (count--) {
        *values = SwapLowWordBytes(*values);
        ++values;
    }
    return 0;
}
#pragma code_seg()
