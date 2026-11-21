struct RuntimeException4 {
    RuntimeException4* Destroy(unsigned char flags);
};
extern "C" void __fastcall crt_helper_4623de(RuntimeException4*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException4* RuntimeException4::Destroy(unsigned char flags) {
    crt_helper_4623de(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
