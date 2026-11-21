// 0x0044C590: snap both components of a vector to multiples of 0.01.
#include <math.h>

struct Vector25 {
    float x;
    float y;

    void SnapToHundredths();
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void Vector25::SnapToHundredths() {
    x = (float)floor(x * 100.0f) * 0.01f;
    y = (float)floor(y * 100.0f) * 0.01f;
}
#pragma code_seg()
