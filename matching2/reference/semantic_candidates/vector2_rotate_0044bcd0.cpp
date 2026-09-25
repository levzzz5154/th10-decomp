#include <math.h>

struct Vector2f_0044bcd0 {
    float x;
    float y;
};

// Retail 0x0044BCD0..0x0044BCF7 receives source in EAX, target in ECX,
// and the angle as a callee-cleanup stack argument.
extern "C" void __cdecl RotateVector2_0044bcd0(
    Vector2f_0044bcd0* target, const Vector2f_0044bcd0* source,
    float radians) {
    const double sine = sin(radians);
    const double cosine = cos(radians);

    target->x = static_cast<float>(cosine * source->x - sine * source->y);
    // Retail reads the source again after storing x, including when aliased.
    target->y = static_cast<float>(sine * source->x + cosine * source->y);
}
