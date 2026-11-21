struct RuntimeException11 {
    RuntimeException11* Destroy(unsigned char flags);
};
extern "C" void __fastcall crt_type_info(RuntimeException11*);
extern "C" void __cdecl crt_free_startup(void*);
RuntimeException11* RuntimeException11::Destroy(unsigned char flags) {
    crt_type_info(this);
    if (flags & 1)
        crt_free_startup(this);
    return this;
}
