// 0x00408C90: create the player manager. A manager that fails to initialize is destroyed
// again and the factory returns null; the compiler-generated cleanup at
// 0x00465860 frees the block if the constructor throws.
#include "th10/game/player_manager_create_00408c90.hpp"

#pragma code_seg(".text$04create")
PlayerManager_00408c90* __stdcall PlayerManager_Create_00408c90() {
    PlayerManager_00408c90* manager = new PlayerManager_00408c90;
    if (manager->Initialize()) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()
