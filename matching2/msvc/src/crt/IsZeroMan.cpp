// 0x0045D3E2..0x0045D3FA: True when all three mantissa words are zero.
extern "C" int __cdecl crt_IsZeroMan(const int* words) {
    int index = 0;
    do {
        if (words[index] != 0) return 0;
        ++index;
    } while (index < 3);
    return 1;
}
