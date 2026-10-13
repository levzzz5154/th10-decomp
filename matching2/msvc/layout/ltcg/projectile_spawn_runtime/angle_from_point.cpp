// Compiler context only: the anchor copy of 0x00426660, returning the angle
// from a supplied point to the player origin. The whole-program pass derives
// the point-in-EAX convention from the spawn path's call sites. The anchor
// bytes are never exported as recovered code.
#include <math.h>

extern "C" const float data_00470b04;
extern "C" const float data_00470b94;

struct EntityAngleFromPoint_00426660 {
    unsigned char reserved_000[0x3C0];
    float origin_x;
    float origin_y;

    __declspec(noinline) float AngleFromPoint(const float* point);
};

#pragma code_seg(".text$00426660_s")
float EntityAngleFromPoint_00426660::AngleFromPoint(const float* point) {
    float dx = origin_x - point[0];
    float dy = origin_y - point[1];
    if (dy == data_00470b04 && dx == data_00470b04)
        return data_00470b94;
    return (float)atan2((double)dy, (double)dx);
}
#pragma code_seg()
