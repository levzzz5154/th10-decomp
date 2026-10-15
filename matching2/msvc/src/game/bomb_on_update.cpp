// 0x00405840: the bomb's update task; runs Bomb::Update (0x00405750).
#include "th10/game/bomb_state.hpp"
// The primary scheduler passes its actual player context in ECX.
#pragma code_seg(".text$036callback")
__declspec(noinline) int __fastcall Bomb_OnUpdate(void* context) {
    return static_cast<BombState*>(context)->Update();
}
#pragma code_seg()
