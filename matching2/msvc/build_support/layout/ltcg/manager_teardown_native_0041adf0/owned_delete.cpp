#include "th10/game/item_manager_destructor.hpp"
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall ManagerTeardown_DestroyOwned_0041AFB0(ItemManager* manager) {
 if(manager) { manager->~ItemManager(); ::operator delete(manager); }
}
#pragma code_seg()
