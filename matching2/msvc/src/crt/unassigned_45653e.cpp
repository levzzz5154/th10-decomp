extern "C" unsigned int (__stdcall *imp_GetCurrentThreadId)();
extern "C" unsigned int (__stdcall *imp_GetCurrentThread)();

// GetCurrentThreadId and GetCurrentThread import forwarders.
extern "C" unsigned int __stdcall import_GetCurrentThreadId() {
    return imp_GetCurrentThreadId();
}
extern "C" unsigned int __stdcall import_GetCurrentThread() {
    return imp_GetCurrentThread();
}
