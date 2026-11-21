extern "C" int __cdecl crt_unassigned_45ebf5(double value) {
    unsigned int bits = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&value) + 6);
    return static_cast<short>(((bits >> 4) & 0xFFFF07FF) - 0x3FE);
}
