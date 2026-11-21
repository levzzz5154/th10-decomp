struct RuntimeException24 {
    RuntimeException24* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_exception_00462cac(RuntimeException24*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException24* RuntimeException24::Destroy(unsigned char flags) {
    asm_exception_00462cac(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
