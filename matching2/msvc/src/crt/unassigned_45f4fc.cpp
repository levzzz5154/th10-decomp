extern "C" int __cdecl crt_x_ismbbtype(unsigned int character, int locale, int mask);

extern "C" int __cdecl crt_unassigned_45f4fc(unsigned int character) {
    return crt_x_ismbbtype(character, 0x0, 1);
}

extern "C" int __cdecl crt_ismbbtype_wrapper(unsigned int character) {
    return crt_x_ismbbtype(character, 0x0, 3);
}

extern "C" int __cdecl crt_ismbbtype_wrapper_45f51e(unsigned int character) {
    return crt_x_ismbbtype(character, 0x0, 2);
}

extern "C" int __cdecl crt_ismbbtype_wrapper_45f52f(unsigned int character) {
    return crt_x_ismbbtype(character, 0x107, 1);
}

extern "C" int __cdecl crt_ismbbtype_wrapper_45f543(unsigned int character) {
    return crt_x_ismbbtype(character, 0x103, 1);
}

extern "C" int __cdecl crt_ismbbtype_wrapper_45f557(unsigned int character) {
    return crt_x_ismbbtype(character, 0x117, 3);
}

extern "C" int __cdecl crt_ismbbtype_wrapper_45f56b(unsigned int character) {
    return crt_x_ismbbtype(character, 0x157, 3);
}

extern "C" int __cdecl crt_ismbbtype_wrapper_45f57f(unsigned int character) {
    return crt_x_ismbbtype(character, 0x10, 2);
}

