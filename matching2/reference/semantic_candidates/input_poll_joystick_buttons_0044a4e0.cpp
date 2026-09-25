#include <string.h>

// Existing inline-assembly callers name the old cdecl symbol. The routine's
// retail entry uses ECX and returns its state buffer in EAX.
#pragma comment(linker, "/alternatename:_asm_Input_PollJoystickButtons_0044a4e0=@Input_PollJoystickButtons_0044A4E0@4")
#pragma comment(linker, "/alternatename:@asm_Input_PollJoystickButtons_0044a4e0@4=@Input_PollJoystickButtons_0044A4E0@4")

// The WinMM branch needs the retail JOYINFOEX fields through dwButtons.
struct JoystickInfoEx_0044a4e0 {
    unsigned int dwSize;
    unsigned int dwFlags;
    unsigned int dwXpos;
    unsigned int dwYpos;
    unsigned int dwZpos;
    unsigned int dwRpos;
    unsigned int dwUpos;
    unsigned int dwVpos;
    unsigned int dwButtons;
    unsigned int dwButtonNumber;
    unsigned int dwPOV;
    unsigned int dwReserved1;
    unsigned int dwReserved2;
};

typedef unsigned int (__stdcall *JoyGetPosEx_0044a4e0)(
        unsigned int device, JoystickInfoEx_0044a4e0* info);
typedef long (__stdcall *DirectInputPoll_0044a4e0)(void* device);
typedef long (__stdcall *DirectInputAcquire_0044a4e0)(void* device);
typedef long (__stdcall *DirectInputGetState_0044a4e0)(
        void* device, unsigned int size, void* state);

extern "C" unsigned char data_00466280; // joyGetPosEx import slot
extern "C" unsigned char data_00491c3c; // DirectInput device pointer table
extern "C" unsigned int data_00491ff4; // input mode flags
extern "C" unsigned char data_00497bb0; // 128-byte button state

// 0x0044A4E0..0x0044A5E7: return the shared byte-per-button state buffer.
// The pad index arrives in ECX. The only caller passes zero, but the
// DirectInput branch indexes the device table with the supplied value.
extern "C" unsigned char* __fastcall
Input_PollJoystickButtons_0044A4E0(int pad_index) {
    unsigned char* const output = &data_00497bb0;

    // Retail clears all 32 dwords (128 bytes) before selecting a backend.
    for (unsigned int index = 0; index != 128; ++index)
        output[index] = 0;

    if ((data_00491ff4 & 0x400u) == 0) {
        JoystickInfoEx_0044a4e0 info = {};
        info.dwSize = sizeof(info);
        info.dwFlags = 0xFF;

        // The WinMM path always queries device zero; pad_index is ignored.
        JoyGetPosEx_0044a4e0 get_position =
                *reinterpret_cast<JoyGetPosEx_0044a4e0*>(&data_00466280);
        if (get_position(0, &info) == 0) {
            unsigned int buttons = info.dwButtons;
            for (unsigned int index = 0; index != 32; ++index) {
                if ((buttons & 1u) != 0)
                    output[index] = 0x80;
                buttons >>= 1;
            }
        }
        // A failed joyGetPosEx leaves the already-cleared buffer untouched.
    } else {
        // Retail dereferences this table entry and its vtable without null or
        // range checks. The three method slots correspond to +0x64, +0x1C,
        // and +0x24 in the live listing.
        void* device = reinterpret_cast<void**>(&data_00491c3c)[pad_index];
        void** vtable = *reinterpret_cast<void***>(device);
        DirectInputPoll_0044a4e0 poll =
                reinterpret_cast<DirectInputPoll_0044a4e0>(vtable[0x64 / 4]);

        if (poll(device) >= 0) {
            // The retail success path reloads the table entry after Poll.
            device = reinterpret_cast<void**>(&data_00491c3c)[pad_index];
            vtable = *reinterpret_cast<void***>(device);
            DirectInputGetState_0044a4e0 get_state =
                    reinterpret_cast<DirectInputGetState_0044a4e0>(
                            vtable[0x24 / 4]);

            // Retail does not initialize this 0x110-byte stack state buffer,
            // checks no GetDeviceState result, and copies all 128 rgbButtons.
            unsigned char direct_input_state[0x110];
            get_state(device, 0x110, direct_input_state);
            memcpy(output, direct_input_state + 0x30, 128);
        } else {
            // The first Acquire also reloads the table entry; each retry
            // below repeats that load before reaching the vtable slot.
            device = reinterpret_cast<void**>(&data_00491c3c)[pad_index];
            vtable = *reinterpret_cast<void***>(device);
            DirectInputAcquire_0044a4e0 acquire =
                    reinterpret_cast<DirectInputAcquire_0044a4e0>(
                            vtable[0x1C / 4]);
            const unsigned int input_lost = 0x8007001Eu;
            long acquire_result = acquire(device);

            // One initial Acquire is followed by at most 400 retries, and
            // only DIERR_INPUTLOST causes another call. Retail does not poll
            // or fetch state again after acquisition succeeds.
            for (unsigned int retry = 0;
                 static_cast<unsigned int>(acquire_result) == input_lost &&
                         retry != 400;
                 ++retry) {
                device = reinterpret_cast<void**>(
                        &data_00491c3c)[pad_index];
                vtable = *reinterpret_cast<void***>(device);
                acquire = reinterpret_cast<DirectInputAcquire_0044a4e0>(
                        vtable[0x1C / 4]);
                acquire_result = acquire(device);
            }
        }
    }

    return output;
}
