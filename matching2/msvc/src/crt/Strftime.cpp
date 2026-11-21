struct ThreadData { unsigned char padding[0x64]; void* locale; };
extern "C" ThreadData* __cdecl crt_getptd();
extern "C" void* __cdecl crt_updatetlocinfo();
extern "C" void* g_crt_locale_data;
extern "C" unsigned int __cdecl crt_helper_45af1d(void*, char*, unsigned int, const char*, const void*, void*);

extern "C" unsigned int __cdecl crt_Strftime(char* output, unsigned int capacity, const char* format, const void* time, void* locale_data) {
    void* locale = crt_getptd()->locale;
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();
    return crt_helper_45af1d(locale, output, capacity, format, time, locale_data);
}
