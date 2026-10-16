extern "C" const char** g_crt_locale_names;
extern "C" unsigned int __cdecl asm_strlen_00456720(const char*);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);
extern "C" char* __cdecl asm_FUN_0045bd80_0045bd80(char*, const char*);

extern "C" char* __cdecl asm_Getmonths_0045a496() {
    const char** names = g_crt_locale_names;
    unsigned int length = 0;
    for (unsigned int i = 0; i < 12; ++i)
        length += asm_strlen_00456720(names[26 + i]) + asm_strlen_00456720(names[14 + i]) + 2;
    char* result = static_cast<char*>(asm_malloc_00452706(length + 1));
    if (result) {
        char* output = result;
        for (unsigned int i = 0; i < 12; ++i) {
            *output++ = ':';
            output += asm_strlen_00456720(asm_FUN_0045bd80_0045bd80(output, names[14 + i]));
            *output++ = ':';
            output += asm_strlen_00456720(asm_FUN_0045bd80_0045bd80(output, names[26 + i]));
        }
        *output = 0;
    }
    return result;
}
