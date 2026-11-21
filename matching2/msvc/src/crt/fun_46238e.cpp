struct RuntimeException2 {
    RuntimeException2* Destroy(unsigned char flags);
};
extern "C" void __fastcall crt_helper_462371(RuntimeException2*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException2* RuntimeException2::Destroy(unsigned char flags) {
    crt_helper_462371(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
