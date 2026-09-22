extern "C" unsigned int __cdecl asm_controlfp_00461090(unsigned int new_value, unsigned int mask);

extern "C" void __cdecl asm_setdefaultprecision_0045dfe8() {
    asm_controlfp_00461090(0x10000, 0x30000);
}
