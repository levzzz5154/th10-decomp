extern "C" int __cdecl crt_x_ismbbtype(unsigned int character, int locale, int mask);

extern "C" int __cdecl crt_ismbblead(unsigned int character) {
    return crt_x_ismbbtype(character, 0, 4);
}
