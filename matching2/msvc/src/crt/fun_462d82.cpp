struct RuntimeException24 {
    RuntimeException24* Destroy(unsigned char flags);
};
extern "C" void __fastcall crt_exception(RuntimeException24*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException24* RuntimeException24::Destroy(unsigned char flags) {
    crt_exception(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
