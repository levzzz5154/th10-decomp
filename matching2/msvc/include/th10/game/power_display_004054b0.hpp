#pragma once
// The digit owner shared with the unchanged 0x004054B0 implementation.
#include "th10/render/animation_object_0043e5a0.hpp"

struct PowerDisplayOwner_004054b0 {
    unsigned char reserved_0000[0x6A8C];
    unsigned char whole_digit[0x71E4 - 0x6A8C];        // +0x6A8C
    unsigned char tens_digit[0x7590 - 0x71E4];         // +0x71E4
    unsigned char ones_digit[0x9EC8 - 0x7590];         // +0x7590
    Resource_0043e5a0* sprites;                        // +0x9EC8

    __declspec(noinline) void SetPowerDigits(int whole, int fraction);
};

