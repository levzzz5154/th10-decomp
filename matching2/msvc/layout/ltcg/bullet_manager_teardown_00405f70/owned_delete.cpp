#include "th10/game/bullet_manager_teardown_00405f70.hpp"
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall BulletManager_DestroyOwned_00406140(BulletManager_00405F70* manager) {
 if(manager) { manager->~BulletManager_00405F70(); ::operator delete(manager); }
}
#pragma code_seg()
