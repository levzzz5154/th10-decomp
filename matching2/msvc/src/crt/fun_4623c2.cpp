struct RuntimeException4 {
    RuntimeException4* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_004623de_004623de(RuntimeException4*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException4* RuntimeException4::Destroy(unsigned char flags) {
    asm_FUN_004623de_004623de(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
