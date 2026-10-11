#include <stddef.h>
#include <string.h>
struct JOYINFOEX_ { unsigned long dwSize, dwFlags, dwXpos, dwYpos, dwZpos, dwRpos, dwUpos, dwVpos, dwButtons, dwButtonNumber, dwPOV, dwReserved1, dwReserved2; };
struct JOYCAPS_ {
    unsigned short wMid, wPid; char szPname[32];
    unsigned int wXmin, wXmax, wYmin, wYmax, wZmin, wZmax, wNumButtons, wPeriodMin, wPeriodMax;
    unsigned int wRmin, wRmax, wUmin, wUmax, wVmin, wVmax, wCaps, wMaxAxes, wNumAxes, wMaxButtons;
    char szRegKey[32], szOEMVxD[260];
};
struct DIJOYSTATE2_ {
    long lX, lY, lZ, lRx, lRy, lRz, rglSlider[2]; unsigned long rgdwPOV[4]; unsigned char rgbButtons[128];
    long v[8], a[8], f[8];
};
struct PadDevice;
struct PadDeviceVtbl {
    void* m0[7];
    long (__stdcall *Acquire)(PadDevice*);
    void* Unacquire;
    long (__stdcall *GetDeviceState)(PadDevice*, unsigned long, void*);
    void* m10[15];
    long (__stdcall *Poll)(PadDevice*);
};
struct PadDevice { PadDeviceVtbl* vtbl; };
struct InputBinding {
    unsigned char state[0x58];
    short shot, bomb, focus, pause;
    unsigned char keys[8];
    short skip;
};
extern "C" {
__declspec(dllimport) unsigned int __stdcall joyGetPosEx(unsigned int id, JOYINFOEX_* info);
extern unsigned int data_00491ff4;
extern InputBinding data_00474e30[];
extern JOYCAPS_ data_004918b8[];
extern PadDevice* data_00491c3c[];
extern short data_00491d5e, data_00491d60;
}
#define C data_004918b8[pad]
static __forceinline unsigned short ReadImpl(unsigned int mask, InputBinding* binding, int pad) {
    if ((data_00491ff4 & 0x400) == 0) {
        JOYINFOEX_ info;
        memset(&info, 0, sizeof(info));
        info.dwSize = sizeof(info);
        info.dwFlags = 0xff;
        if (joyGetPosEx(pad != 0, &info) != 0) return (unsigned short)mask;
        if (binding->shot >= 0) mask |= (info.dwButtons & (1 << binding->shot)) ? 1 : 0;
        if (binding->bomb >= 0) mask |= (info.dwButtons & (1 << binding->bomb)) ? 2 : 0;
        if (binding->pause >= 0) mask |= (info.dwButtons & (1 << binding->pause)) ? 8 : 0;
        if (binding->focus >= 0) mask |= (info.dwButtons & (1 << binding->focus)) ? 4 : 0;
        if (binding->skip >= 0) mask |= (info.dwButtons & (1 << binding->skip)) ? 0x100 : 0;
        unsigned bx = (C.wXmax - C.wXmin) / 4;
        mask |= (info.dwXpos > (C.wXmin + C.wXmax) / 2 + bx ? 0x80 : 0) | (info.dwXpos < (C.wXmax + C.wXmin) / 2 - bx ? 0x40 : 0);
        unsigned by = (C.wYmax - C.wYmin) / 4;
        mask |= (info.dwYpos < (C.wYmin + C.wYmax) / 2 - by ? 0x10 : 0) | (info.dwYpos > (C.wYmax + C.wYmin) / 2 + by ? 0x20 : 0);
        return (unsigned short)mask;
    }
    if (data_00491c3c[pad]->vtbl->Poll(data_00491c3c[pad]) < 0) {
        int tries = 0;
        long result = data_00491c3c[pad]->vtbl->Acquire(data_00491c3c[pad]);
        while (result == (long)0x8007001e) {
            result = data_00491c3c[pad]->vtbl->Acquire(data_00491c3c[pad]);
            if (++tries >= 400) return (unsigned short)mask;
        }
        return (unsigned short)mask;
    }
    DIJOYSTATE2_ state;
    memset(&state, 0, sizeof(state));
    if (data_00491c3c[pad]->vtbl->GetDeviceState(data_00491c3c[pad], sizeof(state), &state) < 0) return (unsigned short)mask;
    if (binding->shot >= 0) mask |= (state.rgbButtons[binding->shot] & 0x80) ? 1 : 0;
    if (binding->bomb >= 0) mask |= (state.rgbButtons[binding->bomb] & 0x80) ? 2 : 0;
    if (binding->pause >= 0) mask |= (state.rgbButtons[binding->pause] & 0x80) ? 8 : 0;
    if (binding->focus >= 0) mask |= (state.rgbButtons[binding->focus] & 0x80) ? 4 : 0;
    if (binding->skip >= 0) mask |= (state.rgbButtons[binding->skip] & 0x80) ? 0x100 : 0;
    mask |= (state.lX < -data_00491d5e ? 0x40 : 0) | (state.lY < -data_00491d60 ? 0x10 : 0)
          | (state.lX > data_00491d5e ? 0x80 : 0) | (state.lY > data_00491d60 ? 0x20 : 0);
    return (unsigned short)mask;
}

__declspec(noinline) unsigned short __fastcall ReadPad(unsigned int mask, int unused, int set, int pad) {
    return ReadImpl(mask, &data_00474e30[set], pad);
}
