struct RuntimeException14 {
    void* vtable;
    char* message;
    int owns_message;
    RuntimeException14* Init(const RuntimeException14* source);
};
extern "C" unsigned int __cdecl crt_strlen(const char*);
extern "C" void* __cdecl crt_malloc(unsigned int);
extern "C" char* __cdecl crt_strcpy(char*, const char*);
RuntimeException14* RuntimeException14::Init(const RuntimeException14* source) {
    vtable = reinterpret_cast<void*>(0x46ca68);
    char* incoming;
    if (owns_message = source->owns_message) {
        incoming = source->message;
        if (incoming) {
            char* allocated = reinterpret_cast<char*>(crt_malloc(crt_strlen(incoming) + 1));
            message = allocated;
            if (allocated)
                crt_strcpy(allocated, source->message);
        } else {
            message = 0;
        }
    } else {
        incoming = source->message;
        message = incoming;
    }
    return this;
}
