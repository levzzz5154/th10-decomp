extern "C" void __cdecl crt_free(void*);

extern "C" void __cdecl crt_free_startup(void* memory) {
    crt_free(memory);
}
