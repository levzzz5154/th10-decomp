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
extern "C" LocaleData* data_0047320c;
extern "C" LocaleData* __cdecl asm_updatetlocinfo_00455ade();
extern "C" int __cdecl asm_isctype_mt_00455752(LocaleData*, int, int);

static LocaleData* current_locale_004567ab() {
    LocaleData* locale = asm_getptd_00456357()->locale;
    if (locale != data_0047320c) locale = asm_updatetlocinfo_00455ade();
    return locale;
}

extern "C" int __cdecl asm_unassigned_004567ab(int c) {
    LocaleData* locale = current_locale_004567ab();
    if (locale->categories > 1)
        return asm_isctype_mt_00455752(locale, c, 0x103);

    const unsigned short* table = reinterpret_cast<const unsigned short*>(locale->ctype);
    return table[c] & 0x103;
}

extern "C" int __cdecl asm_isupper_004567ea(int c) {
    LocaleData* locale = current_locale_004567ab();
    if (locale->categories > 1)
        return asm_isctype_mt_00455752(locale, c, 0x01);

    return locale->ctype[c * 2] & 0x01;
}

extern "C" int __cdecl asm_islower_00456824(int c) {
    LocaleData* locale = current_locale_004567ab();
    if (locale->categories > 1)
        return asm_isctype_mt_00455752(locale, c, 0x02);

    return locale->ctype[c * 2] & 0x02;
}
