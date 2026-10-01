#include "th10/game/manager_teardown_native_0041adf0.hpp"
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall ManagerTeardown_DestroyOwned_0041AFB0(NativeEffectManager_0041ADF0* manager) {
 if(manager) { manager->~NativeEffectManager_0041ADF0(); ::operator delete(manager); }
}
#pragma code_seg()
