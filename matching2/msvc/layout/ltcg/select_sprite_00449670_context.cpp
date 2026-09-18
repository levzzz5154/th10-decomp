// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_select_sprite_from_current_resource_00449670.cpp"

#pragma code_seg(".text$03context")
void __stdcall SelectSpriteCompilerContext(Object_00449670** items, int count, Resource_00449670* resource) {
    while (count--) {
        (*items++)->SelectSpriteFromCurrentResource(resource);
    }
}
#pragma code_seg()
