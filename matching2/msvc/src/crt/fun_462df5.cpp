struct RuntimeException28 {
    RuntimeException28* Destroy(unsigned char flags);
};
extern "C" void __fastcall crt_helper_462d77(RuntimeException28*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException28* RuntimeException28::Destroy(unsigned char flags) {
    crt_helper_462d77(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
