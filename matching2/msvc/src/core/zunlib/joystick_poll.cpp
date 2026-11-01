// Joystick binding reader (0x0044A190): ORs the buttons and axes of game pad
// `pad` into the action word `buttons`, using the bindings of binding set `set`
// (shot, bomb, focus, pause and skip are pad button numbers; negative means
// unbound). Without the DirectInput flag (0x400) the pad is read through
// winmm's joyGetPosEx and its axes are compared against the quarter-range dead
// zone of the cached JOYCAPS; with it, the DirectInput device is polled
// (re-acquired up to 400 times after DIERR_INPUTLOST) and its axes are compared
// against the configured thresholds. The shape follows the th06 controller
// reader (Controller::GetControllerInput): the button helpers write through a
// pointer to `buttons`, which is what keeps the action word a stack parameter
// until it is promoted to ESI.
//
// The winmm axis tests are th06's: plain `info`/`deadzone` locals, the
// cached caps read directly at every use, and the Y tests written with the
// midpoint threshold on the side th06 puts it. The 8 bytes below `info` in
// retail's frame are the spill slot of the low Y threshold (computed in EBX,
// which the Y position needs). The Y dead zone is spelled as the negated
// min-minus-max difference, which is what loads wYmin first and schedules the
// low threshold's sum ahead of the dead zone, as retail does.
//
// Retail passes `buttons` in ECX and pops `set` and `pad` (RET 8): the LTCG
// private convention the whole-program pass derives from this stack signature
// for a direct caller (the three retail callers at 0x0044A8B8, 0x0044AC96 and
// 0x0044AFEA push pad 0 and the set and load ECX). The exact build compiles
// this file through build_support/layout/ltcg/joystick_poll_context.cpp,
// whose synthetic caller supplies that call. See
// reference/recovery_notes/joystick_poll_0044a190_exact_2026_11_01.md.
#include <string.h>

struct JoyInfoEx {                    // JOYINFOEX
    unsigned long dwSize, dwFlags, dwXpos, dwYpos, dwZpos, dwRpos, dwUpos, dwVpos;
    unsigned long dwButtons, dwButtonNumber, dwPOV, dwReserved1, dwReserved2;
};
struct JoyCaps {                      // JOYCAPSA, 0x194 bytes
    unsigned short wMid, wPid;
    char szPname[32];
    unsigned int wXmin, wXmax, wYmin, wYmax, wZmin, wZmax, wNumButtons, wPeriodMin, wPeriodMax;
    unsigned int wRmin, wRmax, wUmin, wUmax, wVmin, wVmax, wCaps, wMaxAxes, wNumAxes, wMaxButtons;
    char szRegKey[32], szOEMVxD[260];
};
struct DiJoyState2 {                  // DIJOYSTATE2, 0x110 bytes
    long lX, lY, lZ, lRx, lRy, lRz, rglSlider[2];
    unsigned long rgdwPOV[4];
    unsigned char rgbButtons[128];
    long lVX, lVY, lVZ, lVRx, lVRy, lVRz, rglVSlider[2];
    long lAX, lAY, lAZ, lARx, lARy, lARz, rglASlider[2];
    long lFX, lFY, lFZ, lFRx, lFRy, lFRz, rglFSlider[2];
};

struct PadDevice;                     // IDirectInputDevice8A
struct PadDeviceVtbl {
    void* unknown_00[7];
    long (__stdcall* Acquire)(PadDevice*);
    void* Unacquire;
    long (__stdcall* GetDeviceState)(PadDevice*, unsigned long size, void* state);
    void* unknown_28[15];
    long (__stdcall* Poll)(PadDevice*);
};
struct PadDevice { PadDeviceVtbl* vtbl; };

struct InputBinding {                 // one 0x6A-byte binding set
    unsigned char state[0x58];
    short shot, bomb, focus, pause;   // +0x58 pad button numbers
    unsigned char keys[8];
    short skip;                       // +0x68
};

extern "C" {
__declspec(dllimport) unsigned int __stdcall joyGetPosEx(unsigned int id, JoyInfoEx* info);
extern unsigned int g_app_flags;            // input mode flags (0x400: DirectInput pad)
extern InputBinding g_input_keys_raw[];          // binding sets
extern JoyCaps g_joystick_caps[];               // winmm capabilities per pad
extern PadDevice* g_pad_devices[];            // DirectInput device per pad
extern short g_joystick_x_threshold, g_joystick_y_threshold;    // DirectInput X/Y axis thresholds
}

#define JOYSTICK_MIDPOINT(min, max) ((min + max) / 2)
#define JOYSTICK_BUTTON_PRESSED(button, x, y) (x > y ? button : 0)
#define JOYSTICK_BUTTON_PRESSED_INVERT(button, x, y) (x < y ? button : 0)

static unsigned int SetButtonFromControllerInputs(unsigned short* out, short button, int bit,
                                                  unsigned int input) {
    if (button < 0) return 0;
    unsigned int mask = 1 << button;
    *out |= (input & mask ? bit & 0xffff : 0);
    return input & mask ? bit & 0xffff : 0;
}

static unsigned int SetButtonFromDirectInputJoystate(unsigned short* out, short button, int bit,
                                                     unsigned char* input) {
    if (button < 0) return 0;
    *out |= (input[button] & 0x80 ? bit & 0xffff : 0);
    return input[button] & 0x80 ? bit & 0xffff : 0;
}

unsigned short __stdcall ReadPad(unsigned short buttons, int set, int pad) {
    JoyInfoEx info;
    unsigned int deadzone;
    InputBinding* binding = &g_input_keys_raw[set];
    if ((g_app_flags & 0x400) == 0) {
        memset(&info, 0, sizeof(info));
        info.dwSize = sizeof(info);
        info.dwFlags = 0xff;                         // JOY_RETURNALL
        if (joyGetPosEx(pad != 0, &info) != 0) return buttons;
        SetButtonFromControllerInputs(&buttons, binding->shot, 1, info.dwButtons);
        SetButtonFromControllerInputs(&buttons, binding->bomb, 2, info.dwButtons);
        SetButtonFromControllerInputs(&buttons, binding->pause, 8, info.dwButtons);
        SetButtonFromControllerInputs(&buttons, binding->focus, 4, info.dwButtons);
        SetButtonFromControllerInputs(&buttons, binding->skip, 0x100, info.dwButtons);

        deadzone = (g_joystick_caps[pad].wXmax - g_joystick_caps[pad].wXmin) / 4;
        buttons |= JOYSTICK_BUTTON_PRESSED(0x80, info.dwXpos,
                                           JOYSTICK_MIDPOINT(g_joystick_caps[pad].wXmin, g_joystick_caps[pad].wXmax) + deadzone);
        buttons |= JOYSTICK_BUTTON_PRESSED_INVERT(0x40, info.dwXpos,
                                                  JOYSTICK_MIDPOINT(g_joystick_caps[pad].wXmin, g_joystick_caps[pad].wXmax) - deadzone);
        deadzone = -(g_joystick_caps[pad].wYmin - g_joystick_caps[pad].wYmax) / 4;
        buttons |= JOYSTICK_BUTTON_PRESSED_INVERT(0x20, JOYSTICK_MIDPOINT(g_joystick_caps[pad].wYmin, g_joystick_caps[pad].wYmax) + deadzone,
                                                  info.dwYpos);
        buttons |= JOYSTICK_BUTTON_PRESSED_INVERT(0x10, info.dwYpos,
                                                  JOYSTICK_MIDPOINT(g_joystick_caps[pad].wYmin, g_joystick_caps[pad].wYmax) - deadzone);
        return buttons;
    }

    if (g_pad_devices[pad]->vtbl->Poll(g_pad_devices[pad]) < 0) {
        int retryCount = 0;
        long hr = g_pad_devices[pad]->vtbl->Acquire(g_pad_devices[pad]);
        while (hr == (long)0x8007001e) {              // DIERR_INPUTLOST
            hr = g_pad_devices[pad]->vtbl->Acquire(g_pad_devices[pad]);
            if (++retryCount >= 400) return buttons;
        }
        return buttons;
    }
    DiJoyState2 js;
    memset(&js, 0, sizeof(js));
    if (g_pad_devices[pad]->vtbl->GetDeviceState(g_pad_devices[pad], sizeof(js), &js) < 0) return buttons;
    SetButtonFromDirectInputJoystate(&buttons, binding->shot, 1, js.rgbButtons);
    SetButtonFromDirectInputJoystate(&buttons, binding->bomb, 2, js.rgbButtons);
    SetButtonFromDirectInputJoystate(&buttons, binding->pause, 8, js.rgbButtons);
    SetButtonFromDirectInputJoystate(&buttons, binding->focus, 4, js.rgbButtons);
    SetButtonFromDirectInputJoystate(&buttons, binding->skip, 0x100, js.rgbButtons);
    buttons |= JOYSTICK_BUTTON_PRESSED_INVERT(0x40, js.lX, -g_joystick_x_threshold);
    buttons |= JOYSTICK_BUTTON_PRESSED_INVERT(0x10, js.lY, -g_joystick_y_threshold);
    buttons |= JOYSTICK_BUTTON_PRESSED(0x80, js.lX, g_joystick_x_threshold);
    buttons |= JOYSTICK_BUTTON_PRESSED(0x20, js.lY, g_joystick_y_threshold);
    return buttons;
}
