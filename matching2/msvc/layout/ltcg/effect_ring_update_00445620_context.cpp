// Compiler context only; never selected as recovered game code.
#include <math.h>
#include "../../src/core/sprtfunc/effect_ring_update.cpp"

// 0x004458B0 is maintained in src/math/x87_polar_setters.cpp.  This body only
// tells the optimizer what the callee leaves alone (EDX, ESI, EDI, EBX, EBP).
#pragma code_seg(".text$03polar")
__declspec(noinline) Vector2_004458b0* Vector2_004458b0::SetPolar(float angle, float radius) {
    Vector2_004458b0* volatile receiver = this;
    Vector2_004458b0* destination = receiver;
    destination->x = (float)cos(angle) * radius;
    destination->y = (float)sin(angle) * radius;
    return destination;
}
#pragma code_seg(".text$05context")
typedef int (EffectEntity_00445620::*EffectAdvance_00445620)();
typedef Vector2_004458b0* (Vector2_004458b0::*PolarSetter_004458b0)(float, float);
extern "C" void __stdcall EffectRingContext_00445620(EffectAdvance_00445620* advance, PolarSetter_004458b0* setter) {
    *advance = &EffectEntity_00445620::Advance;
    *setter = &Vector2_004458b0::SetPolar;
}
#pragma code_seg()
