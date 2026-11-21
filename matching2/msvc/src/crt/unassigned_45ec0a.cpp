extern "C" double __cdecl crt_set_exp(double value, int exponent);

extern "C" double __cdecl crt_unassigned_45ec0a(double value, int adjust) {
    unsigned int bits = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&value) + 6);
    int exponent = ((bits >> 4) & 0x7FF) + adjust - 0x3FE;
    return crt_set_exp(value, exponent);
}
