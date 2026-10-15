struct ThreadData { unsigned char padding[0x64]; void* locale; };
struct LocaleData { unsigned char padding[0x14]; int code_page; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" LocaleData* __cdecl asm_updatetlocinfo_00455ade();
extern "C" void* g_crt_locale_data;
extern "C" int __cdecl asm_ascii_strnicmp_004617e0(const char*, const char*, unsigned int);
extern "C" int __cdecl asm_tolower_mt_00460c26(LocaleData*, int);

extern "C" int __cdecl asm_strnicmp_004605b7(const unsigned char* left, const unsigned char* right, unsigned int count) {
    LocaleData* locale = static_cast<LocaleData*>(asm_getptd_00456357()->locale);
    if (locale != g_crt_locale_data) locale = asm_updatetlocinfo_00455ade();
    if (count != 0) {
        if (locale->code_page == 0) return asm_ascii_strnicmp_004617e0(
            reinterpret_cast<const char*>(left), reinterpret_cast<const char*>(right), count);
        int a, b;
        do {
            a = asm_tolower_mt_00460c26(locale, *left++);
            b = asm_tolower_mt_00460c26(locale, *right++);
        } while (--count && a && a == b);
        return a - b;
    }
    return 0;
}
