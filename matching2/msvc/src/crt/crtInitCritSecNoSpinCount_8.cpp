extern "C" void (__stdcall *imp_InitializeCriticalSection)(void*);

extern "C" int __stdcall crt_libcmt_initcrit_crtInitCritSecNoSpinCount_8(void* section, unsigned int unused) {
    imp_InitializeCriticalSection(section);
    return 1;
}
