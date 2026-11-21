struct RuntimeException24 {
    RuntimeException24* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_exception_00462cac(RuntimeException24*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException24* RuntimeException24::Destroy(unsigned char flags) {
    asm_exception_00462cac(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
