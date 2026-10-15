#pragma once
#include "th10/math/timer.hpp"

extern "C" float g_game_speed;                        // shared game speed

// Restart a frame timer from zero, initializing it on first use.
inline void FrameTimer_Restart(FrameTimer* timer) {
    if (!(timer->flags & 1u)) {
        timer->current = 0;
        timer->previous = -999999;
        timer->elapsed = 0;
        timer->speed = &g_game_speed;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->elapsed = 0;
    timer->previous = -1;
}

// Timed interpolation of one integer channel of an animation object.
struct AnimationIntInterpolator {
    int initial;                                       // +0x00
    int goal;                                          // +0x04
    int control_1;                                     // +0x08
    int control_2;                                     // +0x0C
    FrameTimer timer;                                  // +0x10
    int end_time;                                      // +0x24
    int mode;                                          // +0x28
};

struct AnimationColorComponents {
    int red, green, blue;
    AnimationColorComponents() {}
    AnimationColorComponents(int red, int green, int blue) : red(red), green(green), blue(blue) {}
    // Widen a byte triple, last component first.
    explicit AnimationColorComponents(const unsigned char* bytes) {
        blue = bytes[2];
        green = bytes[1];
        red = bytes[0];
    }
};

// Timed interpolation of a three-component colour of an animation object.
struct AnimationColorInterpolator {
    AnimationColorComponents initial;                  // +0x00
    AnimationColorComponents goal;                     // +0x0C
    AnimationColorComponents control_1;                // +0x18
    AnimationColorComponents control_2;                // +0x24
    FrameTimer timer;                                  // +0x30
    int end_time;                                      // +0x44
    int mode;                                          // +0x48

};

// The channels the animation VM's timed colour and alpha instructions drive.
struct AnimationInterpolatedObject {
    unsigned char reserved_000[0xBC];
    AnimationColorInterpolator color_0bc;              // +0x0BC
    AnimationIntInterpolator channel_108;              // +0x108
    unsigned char reserved_134[0x1BC - 0x134];
    AnimationColorInterpolator color_1bc;              // +0x1BC
    AnimationIntInterpolator channel_208;              // +0x208

    // 0x00442220
    __declspec(noinline) void StartColor0BC(const unsigned char* initial, const unsigned char* goal,
                                            int end_time, unsigned char mode);
    // 0x00442050
    __declspec(noinline) void StartColor1BC(const unsigned char* initial, const unsigned char* goal,
                                            int end_time, unsigned char mode);

    // 0x00442300
    __declspec(noinline) void StartChannel108(int end_time, unsigned char mode,
                                              unsigned char initial, unsigned char goal);

    // 0x00441F50
    __declspec(noinline) void StartChannel208(int end_time, unsigned char mode,
                                              unsigned char initial, unsigned char goal);
};

typedef char AnimationIntInterpolatorSize[sizeof(AnimationIntInterpolator) == 0x2C ? 1 : -1];
typedef char AnimationInterpolated108[
    offsetof(AnimationInterpolatedObject, channel_108) == 0x108 ? 1 : -1];
typedef char AnimationInterpolated208[
    offsetof(AnimationInterpolatedObject, channel_208) == 0x208 ? 1 : -1];
