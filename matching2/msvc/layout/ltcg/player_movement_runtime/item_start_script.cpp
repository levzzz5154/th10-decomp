#include "th10/game/entity_script_start.hpp"

#include "item_spawn.hpp"

#pragma code_seg(".text$f00404f30F")
__declspec(noinline) void __stdcall Entity_StartScript_00404f30(
        AnimationResource_0043e710* resource, Entity* entity, int script) {
    Entity_Init(entity);
    entity->Position() = Vector3Value(0.0f, 0.0f, 0.0f);
    entity->BasePosition() = Vector3Value(0.0f, 0.0f, 0.0f);
    entity->RenderOffset() = Vector3Value(0.0f, 0.0f, 0.0f);
    EntityTail(entity)->layer_3a1 = 0x10;
    EntityTail(entity)->layer_3a0 = 0x10;
    entity->ScriptIndex() = static_cast<int16_t>(script);
    resource->LoadScript(entity,script);
}
#pragma code_seg()
