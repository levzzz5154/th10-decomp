struct ThreadData { unsigned char padding[0x64]; void* locale; };
struct LocaleData { unsigned char padding[0x14]; int code_page; };
extern "C" ThreadData* __cdecl crt_getptd();
extern "C" LocaleData* __cdecl crt_updatetlocinfo();
extern "C" void* g_crt_locale_data;
extern "C" int __cdecl crt_ascii_strnicmp(const char*, const char*, unsigned int);
extern "C" int __cdecl crt_tolower_mt(LocaleData*, int);

extern "C" int __cdecl crt_strnicmp(const unsigned char* left, const unsigned char* right, unsigned int count) {
    LocaleData* locale = static_cast<LocaleData*>(crt_getptd()->locale);
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();
    if (count != 0) {
        if (locale->code_page == 0) return crt_ascii_strnicmp(
            reinterpret_cast<const char*>(left), reinterpret_cast<const char*>(right), count);
        int a, b;
        do {
            a = crt_tolower_mt(locale, *left++);
            b = crt_tolower_mt(locale, *right++);
        } while (--count && a && a == b);
        return a - b;
    }
    return 0;
}
