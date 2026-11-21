struct RuntimeException11 {
    RuntimeException11* Destroy(unsigned char flags);
};
extern "C" void __fastcall asm_type_info_00462b35(RuntimeException11*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException11* RuntimeException11::Destroy(unsigned char flags) {
    asm_type_info_00462b35(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
