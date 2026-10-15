extern "C" unsigned int (__stdcall *data_0046619c)();
extern "C" unsigned int (__stdcall *data_00466168)();

// GetCurrentThreadId and GetCurrentThread import forwarders.
extern "C" unsigned int __stdcall import_GetCurrentThreadId_0045653e() {
    return data_0046619c();
}
extern "C" unsigned int __stdcall import_GetCurrentThread_00456544() {
    return data_00466168();
}
