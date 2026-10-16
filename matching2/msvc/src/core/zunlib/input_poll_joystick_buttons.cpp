// Poll the selected joystick backend and return the shared 128-byte button state.
// The retail ABI is ordinary fastcall: pad index in ECX, result pointer in EAX.
// Both stack records stay distinct; DirectInput's state is not preinitialized.
#include <string.h>
struct JoystickInfo {
    unsigned int size, flags;
    unsigned int x, y, z, r, u, v;
    unsigned int buttons, buttonNumber, pov, reserved1, reserved2;
};
struct DirectJoystickState {
    int position[6];
    int sliders[2];
    unsigned int pov[4];
    unsigned char buttons[128];
    unsigned char otherState[96];
};
// Unused methods preserve the observed COM vtable slots. The three called
// methods have their real stdcall signatures and offsets (+1C/+24/+64).
struct DirectJoystick {
    virtual void __stdcall Slot00() = 0;
    virtual void __stdcall Slot01() = 0;
    virtual void __stdcall Slot02() = 0;
    virtual void __stdcall Slot03() = 0;
    virtual void __stdcall Slot04() = 0;
    virtual void __stdcall Slot05() = 0;
    virtual void __stdcall Slot06() = 0;
    virtual long __stdcall Acquire() = 0;
    virtual void __stdcall Slot08() = 0;
    virtual long __stdcall GetDeviceState(unsigned int size, DirectJoystickState* state) = 0;
    virtual void __stdcall Slot10() = 0;
    virtual void __stdcall Slot11() = 0;
    virtual void __stdcall Slot12() = 0;
    virtual void __stdcall Slot13() = 0;
    virtual void __stdcall Slot14() = 0;
    virtual void __stdcall Slot15() = 0;
    virtual void __stdcall Slot16() = 0;
    virtual void __stdcall Slot17() = 0;
    virtual void __stdcall Slot18() = 0;
    virtual void __stdcall Slot19() = 0;
    virtual void __stdcall Slot20() = 0;
    virtual void __stdcall Slot21() = 0;
    virtual void __stdcall Slot22() = 0;
    virtual void __stdcall Slot23() = 0;
    virtual void __stdcall Slot24() = 0;
    virtual long __stdcall Poll() = 0;
};
typedef char JoystickInfoSize[(sizeof(JoystickInfo) == 0x34) ? 1 : -1];
typedef char DirectJoystickStateSize[(sizeof(DirectJoystickState) == 0x110) ? 1 : -1];

extern "C" __declspec(dllimport) unsigned int __stdcall joyGetPosEx(unsigned int, JoystickInfo*);
extern "C" unsigned int g_app_flags;
extern "C" DirectJoystick* g_pad_devices[];
extern "C" unsigned char g_joystick_buttons[128];

extern "C" unsigned char* __fastcall Input_PollJoystickButtons2(int padIndex) {
    // Keep the 0x34-byte WinMM and 0x110-byte DirectInput stack records.
    JoystickInfo info;
    DirectJoystickState state;
    memset(g_joystick_buttons, 0, sizeof(g_joystick_buttons));
    if (!(g_app_flags & 0x400)) {
        memset(&info, 0, sizeof(info));
        info.size = sizeof(info);
        info.flags = 0xff;
        if (joyGetPosEx(0, &info) == 0) {
            unsigned int buttons = info.buttons;
            unsigned int i = 0;
            do {
                if (buttons & 1) g_joystick_buttons[i] = 0x80;
                ++i;
                buttons >>= 1;
            } while (i < 32);
        }
    } else {
        if (g_pad_devices[padIndex]->Poll() < 0) {
            // Poll failure attempts acquisition only; no state read follows.
            long result = g_pad_devices[padIndex]->Acquire();
            int retries = 0;
            while ((unsigned long)result == 0x8007001e) {
                result = g_pad_devices[padIndex]->Acquire();
                if (++retries >= 400) break;
            }
        } else {
            g_pad_devices[padIndex]->GetDeviceState(sizeof(state), &state);
            memcpy(g_joystick_buttons, state.buttons, sizeof(state.buttons));
        }
    }
    return g_joystick_buttons;
}
