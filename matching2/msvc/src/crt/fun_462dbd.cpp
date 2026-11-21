struct RuntimeException26 {
    RuntimeException26* Destroy(unsigned char flags);
};
extern "C" void __fastcall crt_helper_462d00(RuntimeException26*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException26* RuntimeException26::Destroy(unsigned char flags) {
    crt_helper_462d00(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
