struct RuntimeException_0046238e {
    RuntimeException_0046238e* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_00462371_00462371(RuntimeException_0046238e*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException_0046238e* RuntimeException_0046238e::Destroy(unsigned char flags) {
    asm_FUN_00462371_00462371(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
