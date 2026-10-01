#include "th10/game/player_update_00405750.hpp"
// The primary scheduler passes its actual player context in ECX.
#pragma code_seg(".text$036callback")
__declspec(noinline) int __fastcall PlayerUpdateCallback_00405840(void* context) {
    return static_cast<PlayerUpdateState_00405750*>(context)->Update();
}
#pragma code_seg()
