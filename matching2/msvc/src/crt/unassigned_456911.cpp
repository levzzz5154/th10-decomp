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

extern "C" ThreadData* __cdecl crt_getptd();
extern "C" LocaleData* g_crt_locale_data;
extern "C" LocaleData* __cdecl crt_updatetlocinfo();
extern "C" int __cdecl crt_isctype_mt(LocaleData*, int, int);

extern "C" int __cdecl crt_unassigned(int c);

// The CRT classifies through the calling thread's locale, refreshing it when
// the global locale changed; multibyte locales defer to _isctype_mt.
#define CTYPE_TEST(c, mask)                                                \
    LocaleData* locale = crt_getptd()->locale;                    \
    if (locale != g_crt_locale_data) locale = crt_updatetlocinfo();  \
    return locale->categories > 1                                          \
        ? crt_isctype_mt(locale, c, mask)                         \
        : locale->ctype[c] & mask

extern "C" int __cdecl crt_unassigned_456911(int c) {
    CTYPE_TEST(c, 0x10);
}

extern "C" int __cdecl crt_target(int c) {
    CTYPE_TEST(c, 0x107);
}

extern "C" int __cdecl crt_isprint(int c) {
    CTYPE_TEST(c, 0x157);
}

extern "C" int __cdecl crt_isgraph(int c) {
    CTYPE_TEST(c, 0x117);
}

extern "C" int __cdecl crt_iscntrl(int c) {
    CTYPE_TEST(c, 0x20);
}

extern "C" int __cdecl crt_isascii(int c) {
    return static_cast<unsigned int>(c) < 0x80u ? 1 : 0;
}

extern "C" int __cdecl crt_toascii(int c) {
    return c & 0x7f;
}

extern "C" int __cdecl crt_iscsymf(int c) {
    if (crt_unassigned(c) != 0 || c == '_') return 1;
    return 0;
}

extern "C" int __cdecl crt_iscsym(int c) {
    if (crt_target(c) != 0 || c == '_') return 1;
    return 0;
}
