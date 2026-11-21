struct LocaleData {
    unsigned char padding0[0x28];
    int categories;
    unsigned char padding1[0x1c];
    unsigned char* ctype;
};
struct ThreadData {
    unsigned char padding[0x64];
    LocaleData* locale;
};
extern "C" ThreadData* __cdecl crt_getptd();
extern "C" LocaleData* g_crt_locale_data;
extern "C" LocaleData* __cdecl crt_updatetlocinfo();
extern "C" int __cdecl crt_isctype_mt(LocaleData*, int, int);

extern "C" int __cdecl crt_isxdigit(int c) {
    LocaleData* locale = crt_getptd()->locale;
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();
    if (locale->categories > 1) return crt_isctype_mt(locale, c, 128);
    return locale->ctype[c * 2] & 128;
}
