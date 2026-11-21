struct RuntimeException28 {
    RuntimeException28* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_00462d77_00462d77(RuntimeException28*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException28* RuntimeException28::Destroy(unsigned char flags) {
    asm_FUN_00462d77_00462d77(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
