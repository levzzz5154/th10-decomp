// 0x00449450..0x00449464: resolve an animation handle and clear it if stale.
#include "th10/render/animation_validate_handle_00449450.hpp"

#pragma code_seg(".text$03validate")
void* __cdecl AnimationManager_00449450::ValidateHandle(AnimationHandle_00449450* handle) {
    AnimationScriptId_00449450 id = { (int)handle->value };
    void* object = Find(data_00491c10, id);
    if (object == 0)
        handle->value = 0;
    return object;
}
#pragma code_seg()
