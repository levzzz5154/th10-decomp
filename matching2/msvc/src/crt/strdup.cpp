extern "C" unsigned int __cdecl crt_strlen(const char*);
extern "C" void* __cdecl crt_malloc(unsigned int);
extern "C" char* __cdecl crt_strcpy(char*, const char*);

extern "C" char* __cdecl crt_strdup(const char* source) {
    if (source) {
        char* copy = static_cast<char*>(crt_malloc(crt_strlen(source) + 1));
        if (copy) return crt_strcpy(copy, source);
    }
    return 0;
}
