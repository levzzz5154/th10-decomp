// Compiler context only; never selected as recovered game code.
#include "../../src/game/effect/polar_motion_step_0040b320.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$0044c360_ctx")
void __stdcall PolarMotionContext(PolarMotion** items, int count) {
    for (int index = 0; index < count; ++index)
        items[index]->Step();
}
#pragma code_seg()
#pragma inline_depth()
