// 0x00449450..0x00449464: resolve an animation handle and clear it if stale.
#include "th10/render/animation_validate_handle.hpp"

#pragma code_seg(".text$03validate")
void* __cdecl AnimationManager15::ValidateHandle(AnimationHandle10* handle) {
    AnimationScriptId2 id = { (int)handle->value };
    void* object = Find(g_sprt_ctrl, id);
    if (object == 0)
        handle->value = 0;
    return object;
}
#pragma code_seg()
