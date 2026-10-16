// RecoveryTimer store, isolated into its own /GL module exactly like the
// proven frame_timer family module: a record type whose flags live at +0x10,
// a noinline store member, plain __thiscall declaration. The interprocedural
// pass picks the receiver's private register for this module.
#include "th10/game/recovery_script_executor.hpp"

extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;

#pragma code_seg(".text$00405410_fn")
void RecoveryTimer2::Set(int value) {
    if (!(flags & 1u)) {
        current = 0;
        previous = static_cast<int>(0xFFF0BDC1u);
        elapsed = 0.0f;
        speed = reinterpret_cast<const float*>(0x00476F78u);
        flags |= 1u;
    }
    current = value;
    previous = value - 1;
    elapsed = static_cast<float>(value);
}
#pragma code_seg(".text$0044bf40_fn")
void RecoveryTimer2::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper)
        elapsed += delta;
    else
        elapsed += delta * *speed;
    current = int(elapsed);
}
#pragma code_seg()
