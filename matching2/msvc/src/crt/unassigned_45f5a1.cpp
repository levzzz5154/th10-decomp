extern "C" int __cdecl crt_x_ismbbtype(unsigned int character, int locale, int mask);
extern "C" unsigned int g_mbc_cp932;

extern "C" int __cdecl crt_unassigned_45f5a1(unsigned int character) {
    return crt_x_ismbbtype(character, 0, 8);
}

extern "C" int __cdecl crt_ismbbtype_3a4(unsigned int character) {
    if (g_mbc_cp932 == 0x3A4 && crt_x_ismbbtype(character, 0, 3)) return 1;
    return 0;
}

