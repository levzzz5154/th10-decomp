struct RuntimeException11 {
    RuntimeException11* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_type_info_00462b35(RuntimeException11*);
extern "C" void __cdecl asm_free_004524a1(void*);
RuntimeException11* RuntimeException11::Destroy(unsigned char flags) {
    asm_type_info_00462b35(this);
    if (flags & 1)
        asm_free_004524a1(this);
    return this;
}
