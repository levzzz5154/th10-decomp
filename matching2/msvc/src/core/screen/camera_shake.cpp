// 0x0043C550: the linear camera shake, update task of screen effect mode 1.
// Advances its timer, interpolates the amplitude, and picks independently
// signed offsets with the game's 16-bit random recurrence.
#include "th10/core/screen.hpp"
extern "C" unsigned g_screen_effects_frozen;
// The game RNG (g_rng); this task reads the seed as one 32-bit word.
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
extern "C" ShakeRngStorage g_rng;
extern "C" float g_screen_shake_x, g_screen_shake_y;
static __forceinline unsigned ShakeRandom() {
    unsigned short next = g_rng.NextWord();
    return (unsigned)next | ((unsigned)next << 16);
}
enum LinearShakeConstants {
    LINEAR_SHAKE_CONTINUE = 1,
    LINEAR_SHAKE_REMOVE = 7,
    LINEAR_SHAKE_ZERO = 0,
    LINEAR_SHAKE_POSITIVE = 1,
    LINEAR_SHAKE_NEGATIVE = 2
};

extern "C" __declspec(noinline) int __fastcall LinearShakeUpdate(void* context) {
    Screen* self = static_cast<Screen*>(context);
    if (g_screen_effects_frozen) return LINEAR_SHAKE_REMOVE;
    self->timer.previous = (unsigned)self->timer.current;
    if (*self->timer.speed > g_frame_timer_normal_lower && *self->timer.speed < g_frame_timer_normal_upper) {
        self->timer.current = (int)((unsigned)self->timer.current + 1u);
        self->timer.elapsed += 1.0f;
    } else {
        self->timer.elapsed += *self->timer.speed;
        self->timer.current = (int)self->timer.elapsed;
    }
    int limit = self->duration_or_strength;
    if (self->timer.current >= limit) return LINEAR_SHAKE_REMOVE;
    int start = self->parameter20;
    int delta = (int)((unsigned)self->parameter24 - (unsigned)start);
    // MATCH: the product is rounded to float and named before the divide: that is
    // the placement retail's code shows, with the fidiv late, inside the
    // second random draw.
    float scaled = (float)((float)delta * self->timer.elapsed);
    float amount = scaled / limit + start;
    ShakeRandom();
    switch (ShakeRandom() % 3u) {
    case LINEAR_SHAKE_ZERO: g_screen_shake_x = 0.0f; break;
    case LINEAR_SHAKE_POSITIVE: g_screen_shake_x = amount; break;
    case LINEAR_SHAKE_NEGATIVE: g_screen_shake_x = -amount; break;
    }
    ShakeRandom();
    switch (ShakeRandom() % 3u) {
    case LINEAR_SHAKE_ZERO: g_screen_shake_y = 0.0f; break;
    case LINEAR_SHAKE_POSITIVE: g_screen_shake_y = amount; break;
    case LINEAR_SHAKE_NEGATIVE: g_screen_shake_y = -amount; break;
    }
    return LINEAR_SHAKE_CONTINUE;
}
