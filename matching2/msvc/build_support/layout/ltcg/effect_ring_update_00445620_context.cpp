// Compiler context only; never selected as recovered game code.
#include <math.h>
#include "../../../src/core/sprtfunc/effect_ring_update.cpp"

// 0x004458B0 is maintained in src/math/x87_polar_setters.cpp.  This body only
// tells the optimizer what the callee leaves alone (EDX, ESI, EDI, EBX, EBP).
#pragma code_seg(".text$03polar")
__declspec(noinline) Vector24* Vector24::SetPolar(float angle, float radius) {
    Vector24* volatile receiver = this;
    Vector24* destination = receiver;
    destination->x = (float)cos(angle) * radius;
    destination->y = (float)sin(angle) * radius;
    return destination;
}
#pragma code_seg(".text$05context")
typedef int (EffectEntity2::*EffectAdvance_00445620)();
typedef Vector24* (Vector24::*PolarSetter_004458b0)(float, float);
extern "C" void __stdcall EffectRingContext_00445620(EffectAdvance_00445620* advance, PolarSetter_004458b0* setter) {
    *advance = &EffectEntity2::Advance;
    *setter = &Vector24::SetPolar;
}
#pragma code_seg()
