extern "C" int __cdecl asm_x_ismbbtype_0045f4c9(unsigned int character, int locale, int mask);
extern "C" unsigned int g_mbc_cp932;

extern "C" int __cdecl asm_unassigned_0045f5a1(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0, 8);
}

extern "C" int __cdecl asm_ismbbtype_3a4_0045f5b2(unsigned int character) {
    if (g_mbc_cp932 == 0x3A4 && asm_x_ismbbtype_0045f4c9(character, 0, 3)) return 1;
    return 0;
}

