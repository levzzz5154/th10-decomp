struct RuntimeException13 {
    void* vtable;
    char* message;
    int owns_message;
    RuntimeException13* Init(const char** source);
};
extern "C" unsigned int __cdecl asm_strlen_00456720(const char*);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);
extern "C" char* __cdecl asm_FUN_0045bd80_0045bd80(char*, const char*);
RuntimeException13* RuntimeException13::Init(const char** source) {
    vtable = reinterpret_cast<void*>(0x46ca68);
    if (*source) {
        char* allocated = reinterpret_cast<char*>(asm_malloc_00452706(asm_strlen_00456720(*source) + 1));
        message = allocated;
        if (allocated)
            asm_FUN_0045bd80_0045bd80(allocated, *source);
    } else {
        message = 0;
    }
    owns_message = 1;
    return this;
}
