// Compiler context only; never selected as recovered game code.
// The keyboard reader is already owned by keyboard_binding_read_0044a9d0;
// keep this call as a fixed-address semantic dependency instead of compiling
// that source a second time in this cluster.
#include "../../../src/unreferenced/FUN_0044a950_0044a950.cpp"
extern unsigned short __fastcall FUN_0044a9d0_0044a9d0(unsigned int binding_set,
                                                       unsigned int unused);

#pragma code_seg(".text$03context")
unsigned short __stdcall BindingReader0044A950Context(unsigned int* items, int count) {
    unsigned short total = 0;
    while (count--) {
        total = (unsigned short)(total + asm_FUN_0044a950_0044a950(
            *items, FUN_0044a9d0_0044a9d0(*items, 0)));
        ++items;
    }
    return total;
}
#pragma code_seg()
