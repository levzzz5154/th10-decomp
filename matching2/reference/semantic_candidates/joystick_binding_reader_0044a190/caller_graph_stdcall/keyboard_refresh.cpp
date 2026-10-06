#include "th10/platform/windows_types.hpp"
#include "joystick_reader.hpp"

// 0x0044A9D0..0x0044AD21: refresh one keyboard binding set from the key state.
//
// The routine snapshots the 256-byte device state (DirectInput when the 0x200
// input mode flag is set, otherwise GetKeyboardState) and packs the keys the
// game binds into a 15-bit mask: bits 0..7 are Z, X, shift, escape, up, down,
// left and right, bits 8..14 are control, Q, S, P/home, return, D and R, and
// the four diagonal pads contribute both of their directions at once. The mask
// is handed to the joystick binding reader, which ORs the bound pad inputs into
// it, and the resulting action word is latched into the binding record: the
// frame's word becomes the previous one, every held key advances its repeat
// counter and the pressed/released edges are derived from the two words.
//

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

extern "C" unsigned int data_004924fc;        // 0x004924FC  input enabled
extern "C" unsigned int data_00491ff4;        // 0x00491FF4  input mode flags
extern "C" KeyboardDevice* data_00491c38;     // 0x00491C38  keyboard device

// Call the complete joystick reader directly.

struct KeyboardBinding_0044a9d0 {          // one 0x6A-byte binding entry
    unsigned short current;                // +0x00  this frame's action word
    unsigned short previous;               // +0x02  last frame's action word
    unsigned short repeat;                 // +0x04  keys that reached the repeat rate
    unsigned short pressed;                // +0x06  newly pressed edges
    unsigned short released;               // +0x08  newly released edges
    unsigned short counters[16];           // +0x0A  hold time of each bound key
    unsigned char unknown_2A[0x6A - 0x2A];
};

#pragma code_seg(".text$a30keyboardrefresh")
extern "C" unsigned short __fastcall RefreshKeyboardBindingSet(unsigned int binding_set) {
    unsigned short mask = 0;
    KeyboardBinding_0044a9d0* binding = (KeyboardBinding_0044a9d0*)
            (0x00474E30 + binding_set * 0x6A);
    BYTE state[256];

    if (data_004924fc) {
        if (!(data_00491ff4 & 0x200)) {
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
            int result = data_00491c38->vtable->GetDeviceState(
                data_00491c38, 256, state);
            mask = 0;
            if (result == (int)0x8007001e) {
                data_00491c38->vtable->Acquire(data_00491c38);
            } else if (result != 0) {
                data_00491c38->vtable->Acquire(data_00491c38);
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

    unsigned short result = JoystickReadBindings(mask, 0, 0);
    binding->previous = binding->current;
    binding->current = result;
    unsigned short bit = 1;
    binding->repeat = 0;
    unsigned short bits = result;
    unsigned short* counter = binding->counters;
    int remaining = 16;
    do {
        if (bits & 1) {
            if (++*counter >= 0x1A) {
                binding->repeat |= bit;
                *counter -= 8;
            }
        } else {
            *counter = 0;
        }
        bits >>= 1;
        ++counter;
        bit <<= 1;
    } while (--remaining);

    unsigned short now = binding->current;
    unsigned short before = binding->previous;
    unsigned short changed = now ^ before;
    binding->pressed = changed & now;
    binding->released = changed & ~now;
    return result;
}
#pragma code_seg()
