// Camera shake task: advance its timer, interpolate amplitude, and choose
// independently signed offsets through the game's 16-bit random recurrence.
#include "th10/core/screen.hpp"
extern unsigned g_shake_cancel;
struct ShakeRngStorage {
    union {
        unsigned int seed_storage;
        struct { unsigned short seed, reserved; } words;
    };
    unsigned int generation;
    __forceinline unsigned short NextWord() {
        unsigned int value = seed_storage ^ 0x9630u;
        value -= 0x6553u;
        unsigned short result = ((unsigned short)value >> 14) + (value << 2);
        words.seed = result;
        ++generation;
        return result;
    }
};
typedef char ShakeRngStorage_size[sizeof(ShakeRngStorage)==8?1:-1];
extern ShakeRngStorage g_camera_shake_rng;
extern float g_camera_shake_x, g_camera_shake_y;
extern float g_timer_unit_low, g_timer_unit_high;
static __forceinline unsigned ShakeRandom() {
    unsigned short next = g_camera_shake_rng.NextWord();
    return (unsigned)next | ((unsigned)next << 16);
}
#pragma code_seg(".text$00camera")
extern "C" __declspec(noinline) int __fastcall LinearShakeUpdate_0043c550(void* context) {
    Screen* self = static_cast<Screen*>(context);
    if (g_shake_cancel) return 7;
    self->timer.previous = (unsigned)self->timer.current;
    if (*self->timer.speed > g_timer_unit_low && *self->timer.speed < g_timer_unit_high) {
        self->timer.current = (int)((unsigned)self->timer.current + 1u);
        self->timer.elapsed += 1.0f;
    } else {
        self->timer.elapsed += *self->timer.speed;
        self->timer.current = (int)self->timer.elapsed;
    }
    int limit = self->duration_or_strength;
    if (self->timer.current >= limit) return 7;
    int start = self->parameter20;
    int delta = (int)((unsigned)self->parameter24 - (unsigned)start);
    float amount = (float)delta * self->timer.elapsed / limit + start;
    ShakeRandom();
    switch (ShakeRandom() % 3u) {
    case 0: g_camera_shake_x = 0.0f; break;
    case 1: g_camera_shake_x = amount; break;
    case 2: g_camera_shake_x = -amount; break;
    }
    ShakeRandom();
    switch (ShakeRandom() % 3u) {
    case 0: g_camera_shake_y = 0.0f; break;
    case 1: g_camera_shake_y = amount; break;
    case 2: g_camera_shake_y = -amount; break;
    }
    return 1;
}

#pragma code_seg()

// Compiler entry only: the real selector stores this callback's address.
typedef int (__fastcall *CameraShakeCallback)(void*);
CameraShakeCallback volatile CameraShakeEntryCallback = LinearShakeUpdate_0043c550;
extern "C" int __stdcall CameraShakeEntry(void* context) {
    return CameraShakeEntryCallback(context);
}
