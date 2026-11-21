#include "../../../src/game/player/player_check_hit.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall FieldContactContext(
        const ContactVector2* positions, TriggerFieldContact* target,
        const ContactVector2* sizes, int count) {
    int result=0;
    while (count--) result += Player_CheckHit(positions++,target,sizes++);
    return result;
}
#pragma code_seg()
