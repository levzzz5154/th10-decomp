extern "C" unsigned long (__stdcall *imp_TlsAlloc)();

extern "C" unsigned long __stdcall asm_FUN_0045631e_0045631e(void*) {
    return imp_TlsAlloc();
}
