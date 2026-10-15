struct ThreadData { unsigned char padding[0x64]; unsigned int* locale; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" unsigned int* __cdecl asm_updatetlocinfo_00455ade();
extern "C" void* g_crt_locale_data;

extern "C" unsigned int __cdecl asm_unassigned_0045bd27() {
    unsigned int* locale = asm_getptd_00456357()->locale;
    if (locale != g_crt_locale_data) locale = asm_updatetlocinfo_00455ade();
    return locale[1];
}

extern "C" unsigned int __cdecl asm_locale_field8_0045bd40() {
    unsigned int* locale = asm_getptd_00456357()->locale;
    if (locale != g_crt_locale_data) locale = asm_updatetlocinfo_00455ade();
    return locale[2];
}

extern "C" unsigned int* __cdecl asm_locale_fieldc_0045bd59() {
    unsigned int* locale = asm_getptd_00456357()->locale;
    if (locale != g_crt_locale_data) locale = asm_updatetlocinfo_00455ade();
    return locale + 3;
}
