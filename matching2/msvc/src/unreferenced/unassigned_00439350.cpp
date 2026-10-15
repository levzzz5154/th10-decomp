// 0x00439350..0x0043938D: push three globals back into the system parameter
// store, then turn the input method editor off.
extern "C" __declspec(dllimport) int __stdcall SystemParametersInfoA(
    unsigned int action, unsigned int param, void* data, unsigned int flags);
extern "C" int __stdcall WINNLSEnableIME_0045232c(void* window, int enable);

extern "C" unsigned int g_screen_saver_active;
extern "C" unsigned int g_screen_saver_timeout;
extern "C" unsigned int g_monitor_power_off;

#pragma code_seg(".text$01accessor")
__declspec(noinline) void ApplySettings_00439350() {
    SystemParametersInfoA(0x11, g_screen_saver_active, 0, 2);
    SystemParametersInfoA(0x55, g_screen_saver_timeout, 0, 2);
    SystemParametersInfoA(0x56, g_monitor_power_off, 0, 2);
    WINNLSEnableIME_0045232c(0, 1);
}
#pragma code_seg()
