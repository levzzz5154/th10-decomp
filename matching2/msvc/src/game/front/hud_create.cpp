// 0x00414830: create the HUD. A manager that fails to initialize is destroyed
// again and the factory returns null; the compiler-generated cleanup at
// 0x00465840 frees the block if the constructor throws.
#include "th10/game/hud_create.hpp"

#pragma code_seg(".text$04create")
Hud* __stdcall Hud_Create() {
    Hud* manager = new Hud;
    if (manager->Initialize()) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()
