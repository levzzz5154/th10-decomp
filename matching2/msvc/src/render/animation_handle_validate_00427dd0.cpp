// 0x00427DD0 (30 bytes): return 1 while an animation handle resolves to an
// object; clear stale ids and return 0 when no object remains. The lookup's
// complete C++ body is co-compiled as an unselected anchor so native LTCG
// derives the retail ESI receiver and stack-passed id.
#include "th10/render/animation_handle.hpp"
struct AnimationLookupContext;
struct AnimationScriptId { int value; };
class AnimationManager { public: void* __fastcall Find(AnimationLookupContext*, AnimationScriptId); };
extern "C" AnimationLookupContext* data_00491c10;
#pragma code_seg(".text$02validate")
int AnimationHandle::Validate() {
    AnimationScriptId id; id.value = (int)value;
    void* object = reinterpret_cast<AnimationManager*>(data_00491c10)->Find(data_00491c10, id);
    if (!object) value = 0;
    return object != 0;
}
#pragma code_seg()
