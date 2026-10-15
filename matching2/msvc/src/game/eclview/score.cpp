#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

extern "C" void* __cdecl memset(void* destination, int value, unsigned int size);

// 0x0040AC20..0x0040AC8C: ?UpdateInputState@@
// Advances the sixteen key-repeat counters and then publishes the pressed and
// released edge masks derived from the current and previous key words.
struct KeyRepeatState {
    unsigned char unknown_00[4];
    unsigned short pressed;              // +0x04
    unsigned char unknown_06[0x26];
    unsigned short held_keys;            // +0x2C
    unsigned short previous_keys;        // +0x2E
    unsigned short repeat_flags;         // +0x30
    unsigned short new_press;            // +0x32
    unsigned short new_release;          // +0x34
    unsigned short unknown_36;
    unsigned short repeat_counters[16];  // +0x38
    unsigned short Update();
};
typedef char KeyRepeatState_size_must_be_88[sizeof(KeyRepeatState) == 0x58 ? 1 : -1];

unsigned short KeyRepeatState::Update() {
    unsigned short held = held_keys;
    pressed = 0;
    unsigned short* counter = repeat_counters;
    for (int index = 0; index < 16; ++index) {
        if (held & 1) {
            if (++*counter >= 26) {
                repeat_flags |= 1;
                *counter -= 8;
            }
        } else {
            *counter = 0;
        }
        held >>= 1;
        ++counter;
    }
    unsigned short now = held_keys;
    unsigned short before = previous_keys;
    unsigned short changed = now ^ before;
    new_press = changed & now;
    unsigned short released = changed & ~now;
    new_release = released;
    return released;
}
// 0x0040AD20..0x0040AD40: clamp the requested signed value to the
// counter's current upper bound. Negative requests become UINT_MAX.
unsigned int __fastcall UpdateBoundedCounter(
        unsigned int requested, unsigned int* counter) {
    unsigned int value = counter[2];
    if (value) {
        if ((int)requested >= (int)value)
            --value;
        else
            value = (((int)requested < 0) - 1) & requested;
    } else {
        value = requested;
    }
    *counter = value;
    return value;
}

// BLOCKED (D2601): closest_byte_count=195; first_diff=unmeasured;
// residual_class=abi; the destructor combines allocator callbacks from fixed
// globals, scheduler removal, a virtual release, and an intrusive-list unlink
// while preserving the retail EBX/EBP/ESI/EDI allocation.  Ordinary C++
// changes the callback/register schedule before the list walk.
// variants_tested=exact retail overlay and the existing scheduler/list
// destructor source shapes; no compiler-readable candidate was measured;
// next_lever=co-compile the scheduler remove/free bindings and the owning
// ScoreExtendedObject layout in a native-LTCG destructor cluster.

// 0x0044B010: recovered in src/platform/keyboard_state.cpp.

// 0x0044B080: recovered in src/platform/keyboard_state.cpp.
