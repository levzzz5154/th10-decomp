// 0x004054B0 (79 bytes): point the three digit sprites of the power display
// at their glyphs: the whole part, then the tens and ones of the fraction.
// Glyph scripts start at index 8 of the display's sprite resource.
//
// Native LTCG passes the owner in ESI and the whole part in EDX; the fraction
// stays on the stack.
#include "th10/render/animation_object_0043e5a0.hpp"

struct PowerDisplayOwner_004054b0 {
    unsigned char reserved_0000[0x6A8C];
    unsigned char whole_digit[0x71E4 - 0x6A8C];        // +0x6A8C
    unsigned char tens_digit[0x7590 - 0x71E4];         // +0x71E4
    unsigned char ones_digit[0x9EC8 - 0x7590];         // +0x7590
    Resource_0043e5a0* sprites;                        // +0x9EC8

    __declspec(noinline) void SetPowerDigits(int whole, int fraction);
};

inline AnimationObject_0043e5a0* DigitSprite_004054b0(unsigned char* storage) {
    return reinterpret_cast<AnimationObject_0043e5a0*>(storage);
}

#pragma code_seg(".text$00m_digits")
void PowerDisplayOwner_004054b0::SetPowerDigits(int whole, int fraction) {
    sprites->ConfigureObject(DigitSprite_004054b0(whole_digit), whole + 8);
    sprites->ConfigureObject(DigitSprite_004054b0(tens_digit), fraction / 10 + 8);
    sprites->ConfigureObject(DigitSprite_004054b0(ones_digit), fraction % 10 + 8);
}
#pragma code_seg()
