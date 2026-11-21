struct ThreadData { unsigned char padding[0x64]; unsigned int* locale; };
extern "C" ThreadData* __cdecl crt_getptd();
extern "C" unsigned int* __cdecl crt_updatetlocinfo();
extern "C" void* g_crt_locale_data;

extern "C" unsigned int __cdecl crt_unassigned_45bd27() {
    unsigned int* locale = crt_getptd()->locale;
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();
    return locale[1];
}

extern "C" unsigned int __cdecl crt_locale_field8() {
    unsigned int* locale = crt_getptd()->locale;
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();
    return locale[2];
}

extern "C" unsigned int* __cdecl crt_locale_fieldc() {
    unsigned int* locale = crt_getptd()->locale;
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();
    return locale + 3;
}
