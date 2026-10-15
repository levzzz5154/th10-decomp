// Synthetic compiler context only; never selected as recovered code.
#include "../../src/game/bullet/enemy_motion_steps.cpp"
#pragma code_seg(".text$03context")
int __stdcall EffectAccelCompilerContext_00407560(EffectAccel_00407560** states, int count) {
    for (int index = 0; index < count; ++index)
        states[index]->Update();
    return 0;
}
#pragma code_seg()
