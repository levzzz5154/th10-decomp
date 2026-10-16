extern "C" int __cdecl asm_x_ismbbtype_0045f4c9(unsigned int character, int locale, int mask);

extern "C" int __cdecl asm_unassigned_0045f4fc(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0x0, 1);
}

extern "C" int __cdecl asm_ismbbtype_wrapper_0045f50d(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0x0, 3);
}

extern "C" int __cdecl asm_ismbbtype_wrapper_0045f51e(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0x0, 2);
}

extern "C" int __cdecl asm_ismbbtype_wrapper_0045f52f(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0x107, 1);
}

extern "C" int __cdecl asm_ismbbtype_wrapper_0045f543(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0x103, 1);
}

extern "C" int __cdecl asm_ismbbtype_wrapper_0045f557(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0x117, 3);
}

extern "C" int __cdecl asm_ismbbtype_wrapper_0045f56b(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0x157, 3);
}

extern "C" int __cdecl asm_ismbbtype_wrapper_0045f57f(unsigned int character) {
    return asm_x_ismbbtype_0045f4c9(character, 0x10, 2);
}

