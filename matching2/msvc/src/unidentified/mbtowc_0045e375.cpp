struct ThreadData { unsigned char padding[0x64]; void* locale; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" void* __cdecl asm_updatetlocinfo_00455ade();
extern "C" void* data_0047320c;
extern "C" int __cdecl asm_mbtowc_mt_0045e2b5(void*, unsigned short*, const char*, unsigned int);

extern "C" int __cdecl asm_mbtowc_0045e375(unsigned short* destination, const char* source, unsigned int size) {
    void* locale = asm_getptd_00456357()->locale;
    if (locale != data_0047320c) locale = asm_updatetlocinfo_00455ade();
    return asm_mbtowc_mt_0045e2b5(locale, destination, source, size);
}
