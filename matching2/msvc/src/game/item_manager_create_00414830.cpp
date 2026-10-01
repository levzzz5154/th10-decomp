// 0x00414830: create the item manager. A manager that fails to initialize is destroyed
// again and the factory returns null; the compiler-generated cleanup at
// 0x00465840 frees the block if the constructor throws.
#include "th10/game/item_manager_create_00414830.hpp"

#pragma code_seg(".text$04create")
ItemManager_00414830* __stdcall ItemManager_Create_00414830() {
    ItemManager_00414830* manager = new ItemManager_00414830;
    if (manager->Initialize()) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()
