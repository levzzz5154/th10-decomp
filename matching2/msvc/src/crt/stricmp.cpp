struct ThreadData { unsigned char padding[0x64]; void* locale; };
struct LocaleData { unsigned char padding[0x14]; int code_page; };
extern "C" ThreadData* __cdecl crt_getptd();
extern "C" LocaleData* __cdecl crt_updatetlocinfo();
extern "C" void* g_crt_locale_data;
extern "C" int __cdecl crt_ascii_stricmp(const char*, const char*);
extern "C" int __cdecl crt_tolower_mt(LocaleData*, int);

extern "C" int __cdecl crt_stricmp(const unsigned char* left, const unsigned char* right) {
    LocaleData* locale = static_cast<LocaleData*>(crt_getptd()->locale);
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();
    if (locale->code_page == 0) return crt_ascii_stricmp(
        reinterpret_cast<const char*>(left), reinterpret_cast<const char*>(right));
    int a, b;
    do {
        a = crt_tolower_mt(locale, *left++);
        b = crt_tolower_mt(locale, *right++);
    } while (a && a == b);
    return a - b;
}
