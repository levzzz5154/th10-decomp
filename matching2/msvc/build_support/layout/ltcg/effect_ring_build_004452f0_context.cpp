// Compiler context only; never selected as recovered game code.
#include <math.h>
#include "../../../src/core/sprtfunc/effect_ring.cpp"

// 0x004458B0 is maintained in src/math/x87_polar_setters.cpp.  This body only
// tells the optimizer what the callee leaves alone.
#pragma code_seg(".text$03polar")
__declspec(noinline) Vector24* Vector24::SetPolar(float angle, float radius) {
    Vector24* volatile receiver = this;
    Vector24* destination = receiver;
    destination->x = (float)cos(angle) * radius;
    destination->y = (float)sin(angle) * radius;
    return destination;
}

// 0x0044B9E0 / 0x0044BB90 are maintained in src/core/zunlib/rng.cpp.
#pragma code_seg(".text$07rng")
unsigned int __fastcall Rng_NextU32(RngState* state) {
    unsigned short first = state->NextWord();
    unsigned short second = state->NextWord();
    return second | (static_cast<unsigned int>(first) << 16);
}
float __fastcall Rng_NextFloatSigned(RngState* state) {
    return Rng_NextU32(state) * (1.0f / 2147483648.0f) - 1.0f;
}

#pragma code_seg(".text$05context")
typedef int (RingEntity::*RingBuild_004452f0)();
typedef Vector24* (Vector24::*PolarSetter_004458b0)(float, float);
extern "C" int __stdcall EffectRingBuildContext_004452f0(RingEntity* entity, PolarSetter_004458b0* setter) {
    *setter = &Vector24::SetPolar;
    return entity->BuildRing();
}
