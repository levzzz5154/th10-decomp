struct RuntimeException_00462d82 {
    RuntimeException_00462d82* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_exception_00462cac(RuntimeException_00462d82*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException_00462d82* RuntimeException_00462d82::Destroy(unsigned char flags) {
    asm_exception_00462cac(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
