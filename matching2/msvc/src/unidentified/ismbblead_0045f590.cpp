extern "C" int __cdecl asm_x_ismbbtype_0045f4c9(unsigned int character, int locale, int mask);

extern "C" int __cdecl asm_ismbblead_0045f590(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0, 4);
}
