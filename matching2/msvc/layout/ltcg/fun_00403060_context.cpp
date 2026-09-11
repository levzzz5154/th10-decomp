// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00403060_00403060.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN00403060CompilerContext(int* values, int count) {
    void (__fastcall* forward)(int) = FUN_00403060_Forward;
    while (count--)
        forward(*values++);
    return 0;
}
#pragma code_seg()
