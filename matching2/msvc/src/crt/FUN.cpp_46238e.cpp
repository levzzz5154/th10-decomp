struct RuntimeException2 {
    RuntimeException2* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_00462371_00462371(RuntimeException2*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException2* RuntimeException2::Destroy(unsigned char flags) {
    asm_FUN_00462371_00462371(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
