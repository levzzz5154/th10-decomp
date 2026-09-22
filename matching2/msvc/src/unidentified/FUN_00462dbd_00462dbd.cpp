struct RuntimeException_00462dbd {
    RuntimeException_00462dbd* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_FUN_00462d00_00462d00(RuntimeException_00462dbd*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException_00462dbd* RuntimeException_00462dbd::Destroy(unsigned char flags) {
    asm_FUN_00462d00_00462d00(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
