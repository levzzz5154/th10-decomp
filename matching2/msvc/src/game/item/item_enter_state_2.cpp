// 0x0041BE40 (46 bytes): move an item to state 2 and restart its sprite on the
// script that belongs to its variant (scripts 0x176 onward of the stage's item
// sprite resource). Always returns 0.
//
// Native LTCG passes the item in EAX.
#include "th10/game/entity_script_start.hpp"
#include "th10/game/item.hpp"

struct AnimationResourceFile;
void __stdcall Entity_StartScript(AnimationResourceFile* resource,
                                           Entity* entity, int script);

#pragma code_seg(".text$00zm_item")
int Item2::EnterState2() {
    state = 2;
    Entity_StartScript(
        reinterpret_cast<AnimationResourceFile*>(g_bullet_manager->item_sprites),
        reinterpret_cast<Entity*>(this),
        variant + 0x176);
    return 0;
}
#pragma code_seg()
