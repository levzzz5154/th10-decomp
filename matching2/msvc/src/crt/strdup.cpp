extern "C" unsigned int __cdecl asm_strlen_00456720(const char*);
extern "C" void* __cdecl crt_malloc(unsigned int);
extern "C" char* __cdecl asm_FUN_0045bd80_0045bd80(char*, const char*);

extern "C" char* __cdecl asm_strdup_00462250(const char* source) {
    if (source) {
        char* copy = static_cast<char*>(crt_malloc(asm_strlen_00456720(source) + 1));
        if (copy) return asm_FUN_0045bd80_0045bd80(copy, source);
    }
    return 0;
}
