#include "th10/platform/windows_types.hpp"

// 0x0043BAF0..0x0043BB23: create the DirectInput device the input subsystem
// keeps in the global at 0x491C34. The object's fourth vtable slot takes the
// device, the caller's descriptor (skipping its four-byte header), the global
// that receives the device handle and a zero flag; a negative result means the
// device had just been created, which the caller reports as a failure in EAX.
extern "C" unsigned char data_00491c34;
extern "C" unsigned char data_00491c3c;

typedef int(__stdcall* DirectInputCreateDeviceFn)(void* device, int descriptor,
                                                  int* handle, int flag);

BOOL __stdcall FUN_0043baf0_0043baf0(int descriptor, int unused) {
    if (*(int*)&data_00491c3c == 0) {
        void* device = *(void**)&data_00491c34;
        int result = ((DirectInputCreateDeviceFn)(*(void***)device)[3])(
            device, descriptor + 4, (int*)&data_00491c3c, 0);
        if (result < 0)
            return 1;
    }
    return 0;
}
