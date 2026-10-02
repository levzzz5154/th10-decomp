// Compiler context only; never selected as recovered game code.
#include "../../src/game/polar_motion_step_0040b320.cpp"

// Model of the advance at 0x0044C2A0, compiled at its retail address so the
// pass hands it the record in ESI. Not recovered: retail adds the x pair in
// the other order and releases the floor argument before the last store.
#pragma code_seg(".text$03advance")
void PolarMotion::Advance() {
    PolarVec3 offset;
    if ((flags & 1) == 0) {
        position.x += velocity.x;
        position.y += velocity.y;
        position.z += velocity.z;
    } else {
        offset.SetPolar(angle, radius);
        offset.z = 0.0f;
        position = offset + velocity;
    }
    position.SnapToHundredths();
}
#pragma code_seg()

#pragma inline_depth(0)
#pragma code_seg(".text$05context")
void __stdcall PolarMotionContext(PolarMotion** items, int count) {
    for (int index = 0; index < count; ++index)
        items[index]->Step();
}
#pragma code_seg()
#pragma inline_depth()
