extern "C" unsigned int __cdecl asm_control87_0046105e(unsigned int, unsigned int);

extern "C" unsigned int __cdecl asm_controlfp_00461090(unsigned int new_value, unsigned int mask) {
    return asm_control87_0046105e(new_value, mask & 0xfff7ffff);
}
