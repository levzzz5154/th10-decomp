typedef int (__stdcall *WINNLSEnableIME_target)(void*, int);
extern "C" unsigned char data_004661fc;

extern "C" __declspec(noinline) int __stdcall asm_WINNLSEnableIME_0045232c(void* window, int enable) {
    return (*reinterpret_cast<WINNLSEnableIME_target*>(&data_004661fc))(window, enable);
}
