extern "C" void (__stdcall *imp_InitializeCriticalSection)(void*);

extern "C" int __stdcall asm_crtInitCritSecNoSpinCount_8_004597fe(void* section, unsigned int unused) {
    imp_InitializeCriticalSection(section);
    return 1;
}
