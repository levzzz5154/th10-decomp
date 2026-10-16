// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtlib/animation_manager_select_sprite_from_current_resource.cpp"

#pragma code_seg(".text$03context")
void __stdcall SelectSpriteCompilerContext(Object36** items, int count, Resource3* resource) {
    while (count--) {
        (*items++)->SelectSpriteFromCurrentResource(resource);
    }
}
#pragma code_seg()
