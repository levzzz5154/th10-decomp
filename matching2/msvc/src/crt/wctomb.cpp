struct ThreadData { unsigned char padding[0x64]; void* locale; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" void* __cdecl asm_updatetlocinfo_00455ade();
extern "C" void* g_crt_locale_data;
extern "C" int __cdecl asm_wctomb_mt_0045a10e(void*, char*, unsigned short);

extern "C" int __cdecl asm_wctomb_0045a16e(char* destination, unsigned short wide) {
    void* locale = asm_getptd_00456357()->locale;
    if (locale != g_crt_locale_data) locale = asm_updatetlocinfo_00455ade();
    return asm_wctomb_mt_0045a10e(locale, destination, wide);
}
