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
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" LocaleData* g_crt_locale_data;
extern "C" LocaleData* __cdecl asm_updatetlocinfo_00455ade();
extern "C" int __cdecl asm_isctype_mt_00455752(LocaleData*, int, int);

extern "C" int __cdecl asm_isdigit_0045685e(int c) {
    LocaleData* locale = asm_getptd_00456357()->locale;
    if (locale != g_crt_locale_data) locale = asm_updatetlocinfo_00455ade();
    if (locale->categories > 1) return asm_isctype_mt_00455752(locale, c, 4);
    return locale->ctype[c * 2] & 4;
}
