#include "th10/platform/windows_types.hpp"

extern "C" __declspec(dllimport) BOOL __stdcall GetKeyboardState(BYTE* state);
extern "C" __declspec(dllimport) BOOL __stdcall SetKeyboardState(BYTE* state);

struct KeyboardDevice;
typedef int (__stdcall *KeyboardDeviceMethod)(KeyboardDevice* device);
typedef int (__stdcall *GetDeviceStateMethod)(KeyboardDevice* device,
                                               unsigned int size, void* state);

struct KeyboardDeviceVtable {
    KeyboardDeviceMethod methods[7];
    KeyboardDeviceMethod Acquire;
    KeyboardDeviceMethod Unacquire;
    GetDeviceStateMethod GetDeviceState;
};

struct KeyboardDevice {
    KeyboardDeviceVtable* vtable;
};

extern int g_input_enabled;
extern unsigned int g_input_mode;
extern KeyboardDevice* g_keyboard_device;

// 0x0044B010: clear and refresh the requested keyboard snapshot. Call sites
// establish destination in EDX while ECX is unconstrained. The unused first
// fastcall parameter is therefore an explicit compiler ABI constraint, not
// semantic state. DirectInput failures trigger one acquire attempt; the
// function reports whether the DirectInput route was selected, not I/O success.
int __fastcall Input_UpdateKeyboardState(void*, BYTE* destination) {
    for (int index = 0; index < 256; ++index)
        destination[index] = 0;

    if (!g_input_enabled)
        return 0;
    if (!(g_input_mode & 0x200)) {
        GetKeyboardState(destination);
        return 0;
    }

    int result = g_keyboard_device->vtable->GetDeviceState(
        g_keyboard_device, 256, destination);
    if (result == (int)0x8007001e) {
        g_keyboard_device->vtable->Acquire(g_keyboard_device);
        return 1;
    }
    if (result != 0)
        g_keyboard_device->vtable->Acquire(g_keyboard_device);
    return 1;
}

// 0x0044B080: discard each key's transient down bit, then publish the
// normalized 256-byte snapshot. Retail ignores both Win32 return values.
void Input_NormalizeKeyboardState() {
    BYTE state[256];
    GetKeyboardState(state);
    for (int index = 0; index < 256; ++index)
        state[index] &= 0x7f;
    SetKeyboardState(state);
}
