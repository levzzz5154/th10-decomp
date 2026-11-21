struct RuntimeException13 {
    void* vtable;
    char* message;
    int owns_message;
    RuntimeException13* Init(const char** source);
};
extern "C" unsigned int __cdecl crt_strlen(const char*);
extern "C" void* __cdecl crt_malloc(unsigned int);
extern "C" char* __cdecl crt_strcpy(char*, const char*);
RuntimeException13* RuntimeException13::Init(const char** source) {
    vtable = reinterpret_cast<void*>(0x46ca68);
    if (*source) {
        char* allocated = reinterpret_cast<char*>(crt_malloc(crt_strlen(*source) + 1));
        message = allocated;
        if (allocated)
            crt_strcpy(allocated, *source);
    } else {
        message = 0;
    }
    owns_message = 1;
    return this;
}
