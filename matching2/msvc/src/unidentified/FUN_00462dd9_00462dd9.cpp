struct RuntimeException_00462dd9 {
    RuntimeException_00462dd9* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_00462d3c_00462d3c(RuntimeException_00462dd9*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException_00462dd9* RuntimeException_00462dd9::Destroy(unsigned char flags) {
    asm_FUN_00462d3c_00462d3c(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
