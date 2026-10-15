#include "th10/platform/windows_types.hpp"

// 0x0044AD30..0x0044B004: publish the key mask of the active input device.
//
// The routine snapshots the 256-byte device state (DirectInput when the 0x200
// input mode flag is set, otherwise GetKeyboardState) and packs the keys the
// game binds into a 15-bit mask: bits 0..7 are Z, X, shift, escape, up, down,
// left and right, bits 8..14 are control, Q, S, P/home, return, D and R, and
// the four diagonal pads contribute both of their directions at once. The mask
// is then handed to the state publisher at 0x0044A190.

// DirectInput keyboard device, as recovered from 0x0044B010.
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

extern "C" __declspec(dllimport) BOOL __stdcall GetKeyboardState(BYTE* state);

extern "C" unsigned int g_input_enabled;        // 0x004924FC  input enabled
extern "C" unsigned int g_app_flags;        // 0x00491FF4  input mode flags
extern "C" KeyboardDevice* g_keyboard_device;     // 0x00491C38  keyboard device

// 0x0044A190 receives the packed mask in ECX and two stack words (the pad index
// and a flag, both zero here); the 8-byte parameter keeps that stack layout.
// The call goes through a function-pointer cast so the callee's name is the
// plain extern "C" one the manifest already binds.
extern "C" void __cdecl asm_FUN_0044a190_0044a190(unsigned short mask, long long args);
typedef void (__fastcall* KeyMaskSink)(unsigned short mask, long long args);

void __cdecl FUN_0044ad30_0044ad30() {
    BYTE state[256];
    unsigned short mask = 0;

    if (g_input_enabled) {
        if (!(g_app_flags & 0x200)) {
            GetKeyboardState(state);

            unsigned char keys = 0;
            keys = (unsigned char)((keys >> 1) | (state[0x5a] & 0x80));
            keys = (unsigned char)((keys >> 1) | (state[0x58] & 0x80));
            keys = (unsigned char)((keys >> 1) | (state[0x10] & 0x80));
            keys = (unsigned char)((keys >> 1) | (state[0x1b] & 0x80));
            keys = (unsigned char)((keys >> 1) |
                                   ((state[0x26] | state[0x68]) & 0x80));
            keys = (unsigned char)((keys >> 1) |
                                   ((state[0x28] | state[0x62]) & 0x80));
            keys = (unsigned char)((keys >> 1) |
                                   ((state[0x25] | state[0x64]) & 0x80));
            keys = (unsigned char)((keys >> 1) |
                                   ((state[0x27] | state[0x66]) & 0x80));

            unsigned short extra = (unsigned short)(state[0x52] & 0x80);
            extra = (unsigned short)((extra << 1) | (state[0x44] & 0x80));
            extra = (unsigned short)((extra << 1) | (state[0x0d] & 0x80));
            extra = (unsigned short)((extra << 1) |
                                     ((state[0x24] | state[0x50]) & 0x80));
            extra = (unsigned short)((extra << 1) | (state[0x53] & 0x80));
            extra = (unsigned short)((extra << 1) | (state[0x51] & 0x80));
            extra = (unsigned short)((extra << 1) | (state[0x11] & 0x80));

            mask = keys;
            mask |= (unsigned short)(extra << 1);
            mask |= (state[0x69] & 0x80) ? 0x90 : 0;
            mask |= (state[0x67] & 0x80) ? 0x50 : 0;
            mask |= (state[0x61] & 0x80) ? 0x60 : 0;
            mask |= (state[0x63] & 0x80) ? 0xa0 : 0;
        } else {
            int result = g_keyboard_device->vtable->GetDeviceState(
                g_keyboard_device, 256, state);
            mask = 0;
            if (result == (int)0x8007001e) {
                g_keyboard_device->vtable->Acquire(g_keyboard_device);
            } else if (result != 0) {
                g_keyboard_device->vtable->Acquire(g_keyboard_device);
            } else {
                unsigned char keys = 0;
                keys = (unsigned char)((keys >> 1) | (state[0x2c] & 0x80));
                keys = (unsigned char)((keys >> 1) | (state[0x2d] & 0x80));
                keys = (unsigned char)((keys >> 1) | (state[0x2a] & 0x80));
                keys = (unsigned char)((keys >> 1) | (state[0x01] & 0x80));
                keys = (unsigned char)((keys >> 1) |
                                       ((state[0xc8] | state[0x48]) & 0x80));
                keys = (unsigned char)((keys >> 1) |
                                       ((state[0x50] | state[0xd0]) & 0x80));
                keys = (unsigned char)((keys >> 1) |
                                       ((state[0xcb] | state[0x4b]) & 0x80));
                keys = (unsigned char)((keys >> 1) |
                                       ((state[0xcd] | state[0x4d]) & 0x80));

                unsigned short extra = (unsigned short)(state[0x13] & 0x80);
                extra = (unsigned short)((extra << 1) | (state[0x20] & 0x80));
                extra = (unsigned short)((extra << 1) | (state[0x1c] & 0x80));
                extra = (unsigned short)((extra << 1) |
                                         ((state[0xc7] | state[0x19]) & 0x80));
                extra = (unsigned short)((extra << 1) | (state[0x1f] & 0x80));
                extra = (unsigned short)((extra << 1) | (state[0x10] & 0x80));
                extra = (unsigned short)((extra << 1) | (state[0x1d] & 0x80));

                mask = keys;
                mask |= (unsigned short)(extra << 1);
                mask |= (state[0x49] & 0x80) ? 0x90 : 0;
                mask |= (state[0x47] & 0x80) ? 0x50 : 0;
                mask |= (state[0x4f] & 0x80) ? 0x60 : 0;
                mask |= (state[0x51] & 0x80) ? 0xa0 : 0;
            }
        }
    }

    ((KeyMaskSink)asm_FUN_0044a190_0044a190)(mask, 0);
}
