// Compiler context only: the anchor copy of 0x00408030, starting a live
// record's vanish. It gives the whole-program pass the callee body so the
// command interpreter's call sites derive the retail ESI receiver. The anchor
// bytes are never exported as recovered code.
#include "th10/game/projectile_spawn_runtime_004067d0.hpp"

extern "C" void* data_004776f0;
extern "C" float data_00476f78;

struct PlayfieldPoint {
    float x, y;
    __declspec(noinline) int OutsideBounds(float horizontal_margin,
                                           float vertical_margin) const;
};

struct PlayerCollisionRecord {
    unsigned int flags;
    int countdown;
    unsigned char reserved_008[0x30c - 8];
    unsigned short animation_state;
    unsigned char reserved_30e[0x3b4 - 0x30e];
    Vec3 position;
    unsigned char reserved_3c0[0x3f0 - 0x3c0];
    float collision_diameter;
    unsigned int reserved_3f4;
    int timer_previous, timer_current;
    float timer_elapsed;
    const float* timer_speed;
    unsigned int timer_flags;
    unsigned char reserved_40c[0x438 - 0x40c];
    int animation_index;
    unsigned char reserved_43c[0x446 - 0x43c];
    unsigned short state;
    unsigned char reserved_448[0x7f0 - 0x448];

    __declspec(noinline) int Activate();
};

struct AnimationRef {
    unsigned char reserved_00[8];
};
struct AnimationResource_0043e710 {
    unsigned short id;
    unsigned char reserved_002[0x11c - 2];
    void** scripts;
    unsigned char reserved_120[4];
    int loading;
    __declspec(noinline) AnimationRef CreateOffset(int index, const Vector3* position);
};

#pragma code_seg(".text$00408030_s")
int PlayerCollisionRecord::Activate() {
    if (state != 2 && state != 1)
        return 0;
    if (!reinterpret_cast<const PlayfieldPoint*>(&position)->OutsideBounds(8.0f, 8.0f)) {
        state = 3;
        animation_state = 1;
        if (animation_index >= 0) {
            reinterpret_cast<AnimationResource_0043e710*>(data_004776f0)
                ->CreateOffset(animation_index,
                               reinterpret_cast<const Vector3*>(&position));
        }
        if (!(timer_flags & 1u)) {
            timer_current = 0;
            timer_previous = -999999;
            timer_elapsed = 0.0f;
            timer_speed = &data_00476f78;
            timer_flags |= 1u;
        }
        timer_current = 0;
        timer_elapsed = 0.0f;
        timer_previous = -1;
        return 1;
    }
    state = 3;
    animation_state = 1;
    flags |= 8;
    return 1;
}
#pragma code_seg()
