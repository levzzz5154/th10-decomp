// 0x00404F30 (202 bytes): reinitialize an animation object and start script
// `script` of `resource` on it, with all three position vectors at the origin.
//
// Native LTCG passes the object in ESI and the script index in EAX; only the
// resource stays on the stack. The index is moved to EBX, where the script
// loader at 0x0043E710 expects it.
#include "th10/game/entity_script_start.hpp"

struct AnimationObjectFile;
struct AnimationResourceFile;
extern "C" void __stdcall LoadScript2(AnimationResourceFile* resource,
                                             AnimationObjectFile* object,
                                             int index);

#pragma code_seg(".text$00404f30_fn")
__declspec(noinline) void __stdcall Entity_StartScript(
        AnimationResourceFile* resource, Entity* entity, int script) {
    Entity_Init(0, entity);
    entity->Position() = Vector3Value(0.0f, 0.0f, 0.0f);
    entity->BasePosition() = Vector3Value(0.0f, 0.0f, 0.0f);
    entity->RenderOffset() = Vector3Value(0.0f, 0.0f, 0.0f);
    EntityTail(entity)->layer_3a1 = 0x10;
    EntityTail(entity)->layer_3a0 = 0x10;
    entity->ScriptIndex() = static_cast<int16_t>(script);
    LoadScript2(resource, reinterpret_cast<AnimationObjectFile*>(entity), script);
}
#pragma code_seg()
