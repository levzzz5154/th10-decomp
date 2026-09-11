// Compiler context only; never selected as recovered game code.
// Calling the member twice from an array walk is what makes LTCG keep the
// resource in ECX and deliver the entity and the index in EAX/EDX.
#include "../../src/game/animation_object_configure_from_resource_0043e5a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimationConfigureCompilerContext(AnimationResource** resources,
                                                AnimationEntity** entities,
                                                int count, int index) {
    AnimationResource** cursor = resources;
    AnimationEntity** entity_cursor = entities;
    while (count--) {
        AnimationResource* resource = *cursor++;
        AnimationEntity* entity = *entity_cursor++;
        resource->ConfigureFromResource(entity, index);
        resource->ConfigureFromResource(entity, index);
    }
    return 0;
}
#pragma code_seg()
