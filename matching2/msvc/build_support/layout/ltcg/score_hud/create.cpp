#include "th10/game/score_hud.hpp"
#pragma code_seg(".text$00448d00_fn")
ResultAnimationId __stdcall ResultAnimation_CreatePrimary(void* file, int script, int layer) {
    Entity* object = reinterpret_cast<ResultAnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = layer;
    object->flags_35C = flags | 0x40000000;
    reinterpret_cast<ResultAnimationResource*>(file)->InitializeObject(object,script);
    return reinterpret_cast<ResultAnimationLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
}
#pragma code_seg()
