// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00403070_00403070.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN00403070CompilerContext(int* values, int count) {
    void (__fastcall* forward)(int) = FUN_00403070_Forward;
    while (count--)
        forward(*values++);
    return 0;
}
#pragma code_seg()
