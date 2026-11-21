struct ThreadData { unsigned char padding[0x64]; void* locale; };
extern "C" ThreadData* __cdecl crt_getptd();
extern "C" void* __cdecl crt_updatetlocinfo();
extern "C" void* g_crt_locale_data;
extern "C" int __cdecl crt_tolower_mt(void*, int);

extern "C" int __cdecl crt_tolower(int character) {
    void* locale = crt_getptd()->locale;
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();
    return crt_tolower_mt(locale, character);
}
