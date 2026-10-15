// 0x004415C0 (57 bytes): start consecutive scripts of `resource` on an array
// of entities, beginning at `script`, and remember the sprite each script
// first selected.
//
// Native LTCG passes the count in EAX, the first script in ECX and the array
// in EDX; only the resource stays on the stack.
#include "th10/game/entity_script_start.hpp"

struct AnimationResourceFile;
void __stdcall Entity_StartScript(AnimationResourceFile* resource,
                                           Entity* entity, int script);

// +0x388: the sprite index the entity's script started with.
inline int16_t& EntityInitialSprite_004415c0(Entity* entity) {
    return *reinterpret_cast<int16_t*>(reinterpret_cast<uint8_t*>(entity) + 0x388);
}

#pragma code_seg(".text$03m_array")
__declspec(noinline) void __stdcall EntityArray_StartScripts_004415c0(
        Entity* entities, int script, int count, AnimationResourceFile* resource) {
    for (; count != 0; --count) {
        Entity_StartScript(resource, entities, script);
        EntityInitialSprite_004415c0(entities) = entities->SpriteIndex();
        ++script;
        ++entities;
    }
}
#pragma code_seg()
