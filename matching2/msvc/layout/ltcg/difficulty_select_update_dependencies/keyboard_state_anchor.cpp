// 0x0044B010, which clears and refreshes a keyboard snapshot, as the practice
// stage selection screen 0x00430FF0 calls it: unselected here, with the one
// parameter its callers pass (the maintained form is
// src/core/zunlib/keyboard_state.cpp).
#include "th10/platform/windows_types.hpp"

extern "C" __declspec(dllimport) BOOL __stdcall GetKeyboardState(BYTE* state);

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

#pragma code_seg(".text$0044b010_fn")
int __stdcall Input_UpdateKeyboardState(BYTE* destination) {
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
#pragma code_seg()
