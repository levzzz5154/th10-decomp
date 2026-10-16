struct ThreadData { unsigned char padding[0x64]; void* locale; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" void* __cdecl asm_updatetlocinfo_00455ade();
extern "C" void* g_crt_locale_data;
extern "C" unsigned int __cdecl asm_FUN_0045af1d_0045af1d(void*, char*, unsigned int, const char*, const void*, void*);

extern "C" unsigned int __cdecl asm_Strftime_0045afe0(char* output, unsigned int capacity, const char* format, const void* time, void* locale_data) {
    void* locale = asm_getptd_00456357()->locale;
    if (locale != g_crt_locale_data) locale = asm_updatetlocinfo_00455ade();
    return asm_FUN_0045af1d_0045af1d(locale, output, capacity, format, time, locale_data);
}
