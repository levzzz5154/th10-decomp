// 0x00406060: create the bullet manager. The inlined constructor builds the
// 2001 bullet slots, clears the block and publishes it; a manager that fails
// to initialize is destroyed again and the factory returns null. The
// compiler-generated cleanup at 0x004658A0 frees the block if a slot
// constructor throws.
#include "th10/game/bullet_manager_create.hpp"

#pragma code_seg(".text$04create")
BulletManager2* __stdcall BulletManager_Create2() {
    BulletManager2* manager = new BulletManager2;
    if (manager->Initialize()) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()
