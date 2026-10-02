#pragma once
#include <stddef.h>
#include <string.h>
#include "th10/game/polar_motion.hpp"

extern "C" float data_00476f78;

struct IndicatorCountdown {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned flags;

    void Set(int frames) {
        if (!(flags & 1)) {
            current = 0;
            previous = -999999;
            elapsed = 0.0f;
            speed = &data_00476f78;
            flags |= 1;
        }
        current = frames;
        previous = frames - 1;
        elapsed = (float)frames;
    }
};

struct IndicatorSlot {
    float width;                         // +00
    float height;                        // +04
    unsigned reserved_08[4];
    PolarMotion motion;                  // +18..43
    IndicatorCountdown timer;            // +44
    unsigned mode;                       // +58
    unsigned counter;                    // +5C
    int limit;                           // +60
    int phase;                           // +64
    unsigned flags;                      // +68
};

struct IndicatorPlayerView {
    unsigned char reserved_0000[0x350C];
    IndicatorSlot slots[32];

    __declspec(noinline) IndicatorSlot* AllocateIndicator(
        const PolarVec3* position, float width, float height,
        int frames, unsigned mode);
};

typedef char IndicatorTimerExtent[sizeof(IndicatorCountdown)==0x14?1:-1];
typedef char IndicatorSlotPositionOffset[offsetof(IndicatorSlot,motion)==0x18?1:-1];
typedef char IndicatorSlotTimerOffset[offsetof(IndicatorSlot,timer)==0x44?1:-1];
typedef char IndicatorSlotFlagsOffset[offsetof(IndicatorSlot,flags)==0x68?1:-1];
typedef char IndicatorSlotExtent[sizeof(IndicatorSlot)==0x6C?1:-1];
typedef char IndicatorPoolOffset[offsetof(IndicatorPlayerView,slots)==0x350C?1:-1];

typedef char PolarVectorExtent[sizeof(PolarVec3)==0x0C?1:-1];
typedef char PolarMotionExtent[sizeof(PolarMotion)==0x2C?1:-1];
typedef char PolarSpeedOffset[offsetof(PolarMotion,speed)==0x18?1:-1];
typedef char PolarRadiusStepOffset[offsetof(PolarMotion,radius_step)==0x24?1:-1];
typedef char PolarPositionOffset[offsetof(PolarMotion,position)==0x00?1:-1];
typedef char PolarVelocityOffset[offsetof(PolarMotion,velocity)==0x0C?1:-1];
typedef char PolarAngleOffset[offsetof(PolarMotion,angle)==0x1C?1:-1];
typedef char PolarRadiusOffset[offsetof(PolarMotion,radius)==0x20?1:-1];
typedef char PolarFlagsOffset[offsetof(PolarMotion,flags)==0x28?1:-1];
