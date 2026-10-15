struct ThreadData { unsigned char padding[0x64]; void* locale; };
struct LocaleData { unsigned char padding[0x14]; int code_page; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" LocaleData* __cdecl asm_updatetlocinfo_00455ade();
extern "C" void* data_0047320c;
extern "C" int __cdecl asm_ascii_stricmp_004603d0(const char*, const char*);
extern "C" int __cdecl asm_tolower_mt_00460c26(LocaleData*, int);

extern "C" int __cdecl asm_stricmp_0046054e(const unsigned char* left, const unsigned char* right) {
    LocaleData* locale = static_cast<LocaleData*>(asm_getptd_00456357()->locale);
    if (locale != data_0047320c) locale = asm_updatetlocinfo_00455ade();
    if (locale->code_page == 0) return asm_ascii_stricmp_004603d0(
        reinterpret_cast<const char*>(left), reinterpret_cast<const char*>(right));
    int a, b;
    do {
        a = asm_tolower_mt_00460c26(locale, *left++);
        b = asm_tolower_mt_00460c26(locale, *right++);
    } while (a && a == b);
    return a - b;
}
