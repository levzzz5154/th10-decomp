// Compiler context only; never selected as recovered game code. The sprite
// destructor is the Entity destructor at 0x00401FF0, visible here so the lone
// sprite member inlines it.
#include "th10/game/front_destroy.hpp"

#pragma code_seg(".text$00sprite_dtor")
FrontSprite::~FrontSprite() {
    if (resource)
        entry_free_00452422(resource);
    resource = 0;
}
#pragma code_seg()

#include "../../../../src/game/front/front_destroy.cpp"
#include "../animation_lookup_anchors.cpp"
#include "../../../../src/core/sprtlib/animation_manager_mark_resource_for_removal_004493e0.cpp"
#define TH10_SCHEDULER_REMOVE_ONLY
#include "../manager_teardown_native_0041adf0/scheduler.cpp"

#pragma code_seg(".text$01b_context")
void __stdcall HudTeardownCompilerContext(Front* manager) {
    delete manager;
}
#pragma code_seg()
