struct ThreadData { unsigned char padding[0x64]; void* locale; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" void* __cdecl asm_updatetlocinfo_00455ade();
extern "C" void* data_0047320c;
extern "C" int __cdecl asm_tolower_mt_00460c26(void*, int);

extern "C" int __cdecl asm_tolower_00460cee(int character) {
    void* locale = asm_getptd_00456357()->locale;
    if (locale != data_0047320c) locale = asm_updatetlocinfo_00455ade();
    return asm_tolower_mt_00460c26(locale, character);
}
