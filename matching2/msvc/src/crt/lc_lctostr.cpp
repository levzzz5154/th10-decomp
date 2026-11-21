extern "C" char* __cdecl crt_strcpy(char*, const char*);
extern "C" void __cdecl crt_strcats(char*, int, ...);

extern "C" void __cdecl crt_lc_lctostr(char* output, const char* locale) {
    crt_strcpy(output, locale);
    const char* part = locale + 0x40;
    if (*part) crt_strcats(output, 2, reinterpret_cast<const char*>(0x46e1c4), part);
    part = locale + 0x80;
    if (*part) crt_strcats(output, 2, reinterpret_cast<const char*>(0x46a9ec), part);
}
