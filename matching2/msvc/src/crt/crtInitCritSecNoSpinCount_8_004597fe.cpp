extern "C" void (__stdcall *data_004660b8)(void*);

extern "C" int __stdcall asm_crtInitCritSecNoSpinCount_8_004597fe(void* section, unsigned int unused) {
    data_004660b8(section);
    return 1;
}
