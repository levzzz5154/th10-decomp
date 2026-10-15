// 0x0041AED0: create the item manager and its 2198 items. The inlined
// constructor builds the items, clears the block and publishes it; a
// manager that fails to initialize is destroyed again and the factory returns
// null. The compiler-generated cleanup at 0x00465800 frees the block if an
// item constructor throws.
#include "th10/game/item_manager_create.hpp"

#pragma code_seg(".text$04create")
ItemManager* __stdcall ItemManager_Create() {
    ItemManager* manager = new ItemManager;
    if (manager->Initialize()) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()
