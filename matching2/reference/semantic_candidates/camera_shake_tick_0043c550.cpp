// Camera shake task: advance its timer, interpolate amplitude, and choose
// independently signed offsets through the game's 16-bit random recurrence.
#include "th10/math/rng.hpp"
extern unsigned g_shake_cancel;
extern RngState g_camera_shake_rng;
extern float g_camera_shake_x, g_camera_shake_y;
extern float g_timer_unit_low, g_timer_unit_high;
struct CameraShakeTask_0043c550 {
    unsigned char reserved[0x1c];
    int duration, amplitude_start, amplitude_end;
    unsigned char reserved_28[8];
    unsigned previous_frame;
    int frame;
    float elapsed;
    float* speed;
    __declspec(noinline) int Tick();
};
static __forceinline unsigned ShakeRandom() {
    unsigned short next = g_camera_shake_rng.NextWord();
    return (unsigned)next | ((unsigned)next << 16);
}
int CameraShakeTask_0043c550::Tick() {
    if (g_shake_cancel) return 7;
    previous_frame = (unsigned)frame;
    if (*speed > g_timer_unit_low && *speed < g_timer_unit_high) {
        frame = (int)((unsigned)frame + 1u);
        elapsed += 1.0f;
    } else {
        elapsed += *speed;
        frame = (int)elapsed;
    }
    int limit = duration;
    if (frame >= limit) return 7;
    int start = amplitude_start;
    int delta = (int)((unsigned)amplitude_end - (unsigned)start);
    float amount = (float)delta * elapsed / limit + start;
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
