// Compiler context only: the anchor copy of 0x00404F30, reinitialising an
// animation object and starting `script` of `resource` on it. It gives the
// whole-program pass the callee body so the spawn path's call sites derive
// the retail register state (object in ESI, script in EAX). The anchor bytes
// are never exported as recovered code.
#include "th10/game/entity_script_start.hpp"
#include "th10/game/entity.hpp"

struct AnimationObjectFile;
struct AnimationResourceFile;
extern "C" void __stdcall LoadScript2(AnimationResourceFile* resource,
                                              AnimationObjectFile* object,
                                              int index);

#pragma code_seg(".text$00404f30_s")
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
