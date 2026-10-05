#ifndef TH10_GAME_TRIGGER_REGION_004267F0_HPP
#define TH10_GAME_TRIGGER_REGION_004267F0_HPP
#include <stddef.h>
#include "th10/math/oriented_rect_contact.hpp"

struct TriggerDialogue_004267f0 {
    unsigned char reserved_000[0x9EB8];
    int active;                         // +0x9EB8
};

// The object tested against rotated rectangles (lasers), as far as 0x004267F0
// reaches it.
struct TriggerField_004267f0 {
    unsigned char reserved_000[0x3C0];
    Point3_OrientedRect position;       // +0x3C0
    unsigned char reserved_3cc[0x41C - 0x3CC];
    Point3_OrientedRect half_size;      // +0x41C
    unsigned char reserved_428[0x458 - 0x428];
    int mode;                           // +0x458
    unsigned char reserved_45c[0x4310 - 0x45C];
    int activation_countdown;           // +0x4310

    // 0x004267F0: classify this object against a rectangle that starts at
    // `origin`, runs `length` along `angle` and is `width` wide. Returns 1
    // (and activates the object) for an overlap, 2 when the object is within
    // three widths of the centre line, 0 otherwise.
    __declspec(noinline) int ClassifyRotatedRegion(const Point3_OrientedRect* origin, float angle, float width,
                                                   float length);
};
typedef char TriggerFieldPositionOffset_004267f0[offsetof(TriggerField_004267f0, position) == 0x3C0 ? 1 : -1];
typedef char TriggerFieldHalfSizeOffset_004267f0[offsetof(TriggerField_004267f0, half_size) == 0x41C ? 1 : -1];
typedef char TriggerFieldModeOffset_004267f0[offsetof(TriggerField_004267f0, mode) == 0x458 ? 1 : -1];
typedef char TriggerFieldCountdownOffset_004267f0[
    offsetof(TriggerField_004267f0, activation_countdown) == 0x4310 ? 1 : -1];

extern "C" {
extern TriggerDialogue_004267f0* data_0047770c;
// 0x00426CF0 takes only the object, on the stack.
void __stdcall ActivateField_00426cf0(TriggerField_004267f0* target);
}

#endif
