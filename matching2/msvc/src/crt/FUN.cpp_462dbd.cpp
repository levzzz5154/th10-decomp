struct RuntimeException26 {
    RuntimeException26* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_00462d00_00462d00(RuntimeException26*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException26* RuntimeException26::Destroy(unsigned char flags) {
    asm_FUN_00462d00_00462d00(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
