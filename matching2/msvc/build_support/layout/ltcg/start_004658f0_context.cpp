// Compiler context only; never selected as recovered game code.
#include "../../../src/static_init/application_init.cpp"
#pragma code_seg(".text$05context")
int __stdcall StartContext_004658f0(int count) {
    int total = 0;
    while (count--) { StaticInit_Application(); total += count; }
    return total;
}
#pragma code_seg()
