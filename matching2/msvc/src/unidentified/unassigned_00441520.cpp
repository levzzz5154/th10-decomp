// 0x00441520..0x00441580: set a run of entities' 16-bit state when the
// animation handle resolves to a loaded resource. Native LTCG preserves the
// count in EAX, entity base in ECX, and the state word on the stack (RET4).
#include <stddef.h>

struct AnimationResourceId_00441520 { int value; };
struct AnimationResource_00441520 {
    unsigned char reserved_000[0x120];
    void* payload_120;
};
struct AnimationManager_00441520 {
    unsigned char reserved_000[0x3AD06C];
    AnimationResource_00441520* resources_3ad06c[0x21];
};
struct AnimationEntity_00441520 {
    unsigned char reserved_000[0x304];
    unsigned short state_304;
    unsigned char reserved_306[0x394-0x306];
    AnimationResourceId_00441520* animation_394;
    unsigned char reserved_398[0x3AC-0x398];
};
// Compile-time checks keep the observed retail layout explicit in MSVC 7.1.
typedef char AnimationEntityStrideCheck_00441520[
    sizeof(AnimationEntity_00441520) == 0x3AC ? 1 : -1];
typedef char AnimationEntityStateOffsetCheck_00441520[
    offsetof(AnimationEntity_00441520, state_304) == 0x304 ? 1 : -1];
typedef char AnimationEntityHandleOffsetCheck_00441520[
    offsetof(AnimationEntity_00441520, animation_394) == 0x394 ? 1 : -1];
typedef char AnimationResourcePayloadOffsetCheck_00441520[
    offsetof(AnimationResource_00441520, payload_120) == 0x120 ? 1 : -1];

extern "C" AnimationManager_00441520* data_00491c10;

// Keeping the resource lookup inline lets native LTCG hoist the manager load
// once, after the zero-count branch, and retain retail's Boolean conversion.
inline int HasLoadedResource_00441520(AnimationResourceId_00441520* handle) {
    AnimationManager_00441520* manager = data_00491c10;
    if (handle == 0) return 0;
    int index = handle->value;
    if (index < 0) return 0;
    AnimationResource_00441520* resource = manager->resources_3ad06c[index];
    if (resource == 0) return 0;
    return resource->payload_120 != 0;
}

#pragma code_seg(".text$01apply")
extern "C" __declspec(noinline) void __stdcall ApplyEntityStateForLoadedResource_00441520(
        unsigned int count, AnimationEntity_00441520* entities, unsigned short state) {
    if (count != 0) {
        AnimationResourceId_00441520** cursor = &entities->animation_394;
        unsigned int remaining = count;
        do {
            if (HasLoadedResource_00441520(*cursor)) {
                AnimationEntity_00441520* entity = (AnimationEntity_00441520*)
                    ((unsigned char*)cursor - 0x394);
                entity->state_304 = state;
            }
            cursor = (AnimationResourceId_00441520**)((unsigned char*)cursor + sizeof(AnimationEntity_00441520));
        } while (--remaining);
    }
}
#pragma code_seg()
