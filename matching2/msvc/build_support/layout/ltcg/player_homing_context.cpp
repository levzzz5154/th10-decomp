#include "../../../src/game/bullet/bullet_ex_home_toward_player.cpp"
#pragma code_seg(".text$03context")
int __stdcall PlayerHomingContext(BulletExHoming** states, int count) {
    for (int i = 0; i < count; ++i)
        states[i]->HomeTowardTarget();
    return count;
}
#pragma code_seg()
