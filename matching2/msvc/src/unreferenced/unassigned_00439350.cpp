// 0x00439350..0x0043938D: push three globals back into the system parameter
// store, then turn the input method editor off.
extern "C" __declspec(dllimport) int __stdcall SystemParametersInfoA(
    unsigned int action, unsigned int param, void* data, unsigned int flags);
extern "C" int __stdcall WINNLSEnableIME_0045232c(void* window, int enable);

extern "C" unsigned int data_0049251c;
extern "C" unsigned int data_00492520;
extern "C" unsigned int data_00492524;

#pragma code_seg(".text$01accessor")
__declspec(noinline) void ApplySettings_00439350() {
    SystemParametersInfoA(0x11, data_0049251c, 0, 2);
    SystemParametersInfoA(0x55, data_00492520, 0, 2);
    SystemParametersInfoA(0x56, data_00492524, 0, 2);
    WINNLSEnableIME_0045232c(0, 1);
}
#pragma code_seg()
