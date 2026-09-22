extern "C" void __cdecl asm_FUN_0045bd80_0045bd80(char*, const char*);
extern "C" void __cdecl asm_strcats_00455990(char*, int, ...);

extern "C" void __cdecl asm_lc_lctostr_00455a90(char* output, const char* locale) {
    asm_FUN_0045bd80_0045bd80(output, locale);
    const char* part = locale + 0x40;
    if (*part) asm_strcats_00455990(output, 2, reinterpret_cast<const char*>(0x46e1c4), part);
    part = locale + 0x80;
    if (*part) asm_strcats_00455990(output, 2, reinterpret_cast<const char*>(0x46a9ec), part);
}
