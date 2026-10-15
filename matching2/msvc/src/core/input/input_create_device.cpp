#include "th10/platform/windows_types.hpp"

// 0x0043BAF0..0x0043BB23: create the DirectInput device the input subsystem
// keeps in the global at 0x491C34. The object's fourth vtable slot takes the
// device, the caller's descriptor (skipping its four-byte header), the global
// that receives the device handle and a zero flag; a negative result means the
// device had just been created, which the caller reports as a failure in EAX.
extern "C" unsigned char g_directinput_keyboard;
extern "C" unsigned char g_pad_devices;

typedef int(__stdcall* DirectInputCreateDeviceFn)(void* device, int descriptor,
                                                  int* handle, int flag);

BOOL __stdcall Input_CreateDevice(int descriptor, int unused) {
    if (*(int*)&g_pad_devices == 0) {
        void* device = *(void**)&g_directinput_keyboard;
        int result = ((DirectInputCreateDeviceFn)(*(void***)device)[3])(
            device, descriptor + 4, (int*)&g_pad_devices, 0);
        if (result < 0)
            return 1;
    }
    return 0;
}
