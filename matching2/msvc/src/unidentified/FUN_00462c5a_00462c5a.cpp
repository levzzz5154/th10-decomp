struct RuntimeException_00462c5a {
    void* vtable;
    char* message;
    int owns_message;
    RuntimeException_00462c5a* Init(const RuntimeException_00462c5a* source);
};
extern "C" unsigned int __cdecl asm_strlen_00456720(const char*);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);
extern "C" void __cdecl asm_FUN_0045bd80_0045bd80(void*, const char*);
RuntimeException_00462c5a* RuntimeException_00462c5a::Init(const RuntimeException_00462c5a* source) {
    vtable = reinterpret_cast<void*>(0x46ca68);
    char* incoming;
    if (owns_message = source->owns_message) {
        incoming = source->message;
        if (incoming) {
            char* allocated = reinterpret_cast<char*>(asm_malloc_00452706(asm_strlen_00456720(incoming) + 1));
            message = allocated;
            if (allocated)
                asm_FUN_0045bd80_0045bd80(allocated, source->message);
        } else {
            message = 0;
        }
    } else {
        incoming = source->message;
        message = incoming;
    }
    return this;
}
