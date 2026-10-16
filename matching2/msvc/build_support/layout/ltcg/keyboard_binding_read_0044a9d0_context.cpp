// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_44a9d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall KeyboardBindingReadCompilerContext(unsigned int* items, int count) {
    unsigned short total = 0;
    while (count--) {
        total = (unsigned short)(total + FUN_0044a9d0_0044a9d0(*items, 0));
        ++items;
    }
    return total;
}
#pragma code_seg()
