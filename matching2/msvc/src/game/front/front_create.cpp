// 0x00414830: create the HUD. A manager that fails to initialize is destroyed
// again and the factory returns null; the compiler-generated cleanup at
// 0x00465840 frees the block if the constructor throws.
#include "th10/game/front_create.hpp"

#pragma code_seg(".text$04create")
Front* __stdcall Front_Create() {
    Front* manager = new Front;
    if (manager->Initialize()) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()
