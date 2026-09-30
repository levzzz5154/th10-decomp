// 0x00401DC0: reinitialize an entity and bind it to one sprite of an
// animation resource. Native LTCG passes the entity in ESI and the resource
// in EDI; only the sprite index stays on the stack.
#include "th10/game/entity.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"

#pragma code_seg(".text$00fn")
__declspec(noinline) int __stdcall Entity_InitFromResource(
        Entity* entity, Resource_0043e5a0* resource, int sprite) {
    Entity_Init(0, entity);
    entity->script_resource = resource;
    return resource->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0*>(entity), sprite);
}
#pragma code_seg()
