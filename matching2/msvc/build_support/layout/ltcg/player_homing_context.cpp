#include "../../../src/game/bullet/player_homing_00407ef0.cpp"
#pragma code_seg(".text$03context")
int __stdcall PlayerHomingContext(PlayerHomingState** states, int count) {
    for (int i = 0; i < count; ++i)
        states[i]->HomeTowardTarget();
    return count;
}
#pragma code_seg()
