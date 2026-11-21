struct RuntimeException7 {
    RuntimeException7* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_0046241d_0046241d(RuntimeException7*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException7* RuntimeException7::Destroy(unsigned char flags) {
    asm_FUN_0046241d_0046241d(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
