extern "C" double __cdecl asm_set_exp_0045ebcb(double value, int exponent);

extern "C" double __cdecl asm_unassigned_0045ec0a(double value, int adjust) {
    unsigned int bits = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&value) + 6);
    int exponent = ((bits >> 4) & 0x7FF) + adjust - 0x3FE;
    return asm_set_exp_0045ebcb(value, exponent);
}
