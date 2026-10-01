// 0x0041AED0: create the manager of the 2198 effect elements. The inlined
// constructor builds the elements, clears the block and publishes it; a
// manager that fails to initialize is destroyed again and the factory returns
// null. The compiler-generated cleanup at 0x00465800 frees the block if an
// element constructor throws.
#include "th10/game/native_effect_manager_create_0041aed0.hpp"

#pragma code_seg(".text$04create")
NativeEffectManager_0041ADF0* __stdcall NativeEffectManager_Create_0041aed0() {
    NativeEffectManager_0041ADF0* manager = new NativeEffectManager_0041ADF0;
    if (manager->Initialize()) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()
