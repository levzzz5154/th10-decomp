#include "th10/game/bullet_manager_teardown.hpp"
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall BulletManager_DestroyOwned_00406140(BulletManager2* manager) {
 if(manager) { manager->~BulletManager2(); ::operator delete(manager); }
}
#pragma code_seg()
