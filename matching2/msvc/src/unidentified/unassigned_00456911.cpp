struct LocaleData {
    unsigned char padding0[0x28];
    int categories;
    unsigned char padding1[0x1c];
    unsigned short* ctype;
};

struct ThreadData {
    unsigned char padding[0x64];
    LocaleData* locale;
};

extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" LocaleData* data_0047320c;
extern "C" LocaleData* __cdecl asm_updatetlocinfo_00455ade();
extern "C" int __cdecl asm_isctype_mt_00455752(LocaleData*, int, int);

extern "C" int __cdecl asm_unassigned_004567ab(int c);

// The CRT classifies through the calling thread's locale, refreshing it when
// the global locale changed; multibyte locales defer to _isctype_mt.
#define CTYPE_TEST(c, mask)                                                \
    LocaleData* locale = asm_getptd_00456357()->locale;                    \
    if (locale != data_0047320c) locale = asm_updatetlocinfo_00455ade();  \
    return locale->categories > 1                                          \
        ? asm_isctype_mt_00455752(locale, c, mask)                         \
        : locale->ctype[c] & mask

extern "C" int __cdecl asm_unassigned_00456911(int c) {
    CTYPE_TEST(c, 0x10);
}

extern "C" int __cdecl asm_target_0045694b(int c) {
    CTYPE_TEST(c, 0x107);
}

extern "C" int __cdecl asm_isprint_0045698a(int c) {
    CTYPE_TEST(c, 0x157);
}

extern "C" int __cdecl asm_isgraph_004569c9(int c) {
    CTYPE_TEST(c, 0x117);
}

extern "C" int __cdecl asm_iscntrl_00456a08(int c) {
    CTYPE_TEST(c, 0x20);
}

extern "C" int __cdecl asm_isascii_00456a42(int c) {
    return static_cast<unsigned int>(c) < 0x80u ? 1 : 0;
}

extern "C" int __cdecl asm_toascii_00456a4f(int c) {
    return c & 0x7f;
}

extern "C" int __cdecl asm_iscsymf_00456a57(int c) {
    if (asm_unassigned_004567ab(c) != 0 || c == '_') return 1;
    return 0;
}

extern "C" int __cdecl asm_iscsym_00456a71(int c) {
    if (asm_target_0045694b(c) != 0 || c == '_') return 1;
    return 0;
}
