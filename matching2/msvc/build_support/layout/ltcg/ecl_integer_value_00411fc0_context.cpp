#include "../../../src/game/enemy/ecl_integer_value_00411fc0.cpp"
#pragma code_seg(".text$06validate")
void* ResolveAnimationHandle(AnimationHandle_00449450* handle) {
    AnimationScriptId_00449450 id = { (int)handle->value };
    void* object = ((AnimationManager_00449450*)g_sprt_ctrl)->Find(g_sprt_ctrl, id);
    if (!object) handle->value = 0;
    return object;
}
#pragma code_seg()
#include "ecl_integer_value_00411fc0_find.cpp"

#pragma code_seg(".text$00context")
extern "C" int __stdcall EclIntegerContext(EclIntegerSource* object, int selector) { return object->ResolveIntegerValue(selector); }
#pragma code_seg()
