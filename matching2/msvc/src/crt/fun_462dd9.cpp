struct RuntimeException27 {
    RuntimeException27* Destroy(unsigned char flags);
};
extern "C" void __fastcall crt_helper_462d3c(RuntimeException27*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException27* RuntimeException27::Destroy(unsigned char flags) {
    crt_helper_462d3c(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
