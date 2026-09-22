struct RuntimeException_004623c2 {
    RuntimeException_004623c2* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_004623de_004623de(RuntimeException_004623c2*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException_004623c2* RuntimeException_004623c2::Destroy(unsigned char flags) {
    asm_FUN_004623de_004623de(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
