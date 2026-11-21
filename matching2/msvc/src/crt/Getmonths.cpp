extern "C" const char** g_crt_locale_names;
extern "C" unsigned int __cdecl crt_strlen(const char*);
extern "C" void* __cdecl crt_malloc(unsigned int);
extern "C" char* __cdecl crt_strcpy(char*, const char*);

extern "C" char* __cdecl crt_Getmonths() {
    const char** names = g_crt_locale_names;
    unsigned int length = 0;
    for (unsigned int i = 0; i < 12; ++i)
        length += crt_strlen(names[26 + i]) + crt_strlen(names[14 + i]) + 2;
    char* result = static_cast<char*>(crt_malloc(length + 1));
    if (result) {
        char* output = result;
        for (unsigned int i = 0; i < 12; ++i) {
            *output++ = ':';
            output += crt_strlen(crt_strcpy(output, names[14 + i]));
            *output++ = ':';
            output += crt_strlen(crt_strcpy(output, names[26 + i]));
        }
        *output = 0;
    }
    return result;
}
