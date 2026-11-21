typedef int (__stdcall *WINNLSEnableIME_target)(void*, int);
extern "C" unsigned char imp_WINNLSEnableIME;

extern "C" __declspec(noinline) int __stdcall Win32_EnableIME(void* window, int enable) {
    return (*reinterpret_cast<WINNLSEnableIME_target*>(&imp_WINNLSEnableIME))(window, enable);
}
