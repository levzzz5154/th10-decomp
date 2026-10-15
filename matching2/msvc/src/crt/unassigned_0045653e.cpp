extern "C" unsigned int (__stdcall *imp_GetCurrentThreadId)();
extern "C" unsigned int (__stdcall *imp_GetCurrentThread)();

// GetCurrentThreadId and GetCurrentThread import forwarders.
extern "C" unsigned int __stdcall import_GetCurrentThreadId_0045653e() {
    return imp_GetCurrentThreadId();
}
extern "C" unsigned int __stdcall import_GetCurrentThread_00456544() {
    return imp_GetCurrentThread();
}
