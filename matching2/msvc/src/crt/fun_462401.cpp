struct RuntimeException7 {
    RuntimeException7* Destroy(unsigned char flags);
};
extern "C" void __fastcall crt_helper_46241d(RuntimeException7*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException7* RuntimeException7::Destroy(unsigned char flags) {
    crt_helper_46241d(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
