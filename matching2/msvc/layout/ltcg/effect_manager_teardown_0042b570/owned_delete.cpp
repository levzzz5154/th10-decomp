#include "th10/game/effect_manager_teardown_0042b570.hpp"
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall EffectManager_DestroyOwned_0042B6D0(EffectManager_0042B570* manager) {
 if(manager) { manager->~EffectManager_0042B570(); ::operator delete(manager); }
}
#pragma code_seg()
