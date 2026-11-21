extern "C" unsigned long (__stdcall *imp_TlsAlloc)();

extern "C" unsigned long __stdcall crt_helper_45631e(void*) {
    return imp_TlsAlloc();
}
