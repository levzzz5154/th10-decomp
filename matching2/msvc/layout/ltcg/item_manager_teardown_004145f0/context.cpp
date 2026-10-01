// Compiler context only; never selected as recovered game code. The sprite
// destructor is the Entity destructor at 0x00401FF0, visible here so the lone
// sprite member inlines it.
#include "th10/game/item_manager_teardown_004145f0.hpp"

#pragma code_seg(".text$00sprite_dtor")
ItemManagerSprite_004145f0::~ItemManagerSprite_004145f0() {
    if (resource)
        entry_free_00452422(resource);
    resource = 0;
}
#pragma code_seg()

#include "../../../src/game/item_manager_teardown_004145f0.cpp"
#include "../animation_lookup_anchors.cpp"
#include "../../../src/render/animation_manager_mark_resource_for_removal_004493e0.cpp"
#define TH10_SCHEDULER_REMOVE_ONLY
#include "../manager_teardown_native_0041adf0/scheduler.cpp"

#pragma code_seg(".text$01b_context")
void __stdcall ItemManagerTeardownCompilerContext(ItemManager_004145f0* manager) {
    delete manager;
}
#pragma code_seg()
