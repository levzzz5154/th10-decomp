#include "th10/game/score_hud_00417040.hpp"
#pragma code_seg(".text$00448d00_fn")
ResultAnimationId __stdcall ResultAnimation_CreatePrimary(void* file, int script, int layer) {
    Entity* object = reinterpret_cast<ResultAnimationPool*>(data_00491c10)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = layer;
    object->flags_35C = flags | 0x40000000;
    reinterpret_cast<ResultAnimationResource*>(file)->InitializeObject(object,script);
    return reinterpret_cast<ResultAnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
}
#pragma code_seg()
