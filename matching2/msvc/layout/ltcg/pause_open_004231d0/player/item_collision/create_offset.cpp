#include "th10/game/pause_result_open_004231d0/player/item_collision/item_collision.hpp"

#pragma code_seg(".text$00448db0_fn")
AnimationScriptId __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, int script, const Vector3* position) {
    Entity* object = static_cast<AnimationPool*>(data_00491c10)->Allocate();
    object->flags_35C |= 0x40000000u;
    object->render_bucket = 0;
    object->position.x = position->x + data_00470b4c;
    object->position.y = position->y + data_00470b48;
    object->position.z = position->z;
    MovementLoadScript_0043e710(
        static_cast<AnimationResource_00449870*>(resource), object, script);
    return static_cast<MovementPrimaryLists*>(data_00491c10)
        ->RegisterPrimaryBack(object);
}
#pragma code_seg()
