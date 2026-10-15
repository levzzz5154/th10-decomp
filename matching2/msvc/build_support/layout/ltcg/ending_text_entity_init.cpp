// 0x00401DE0..0x00401EF0 (273 bytes): Entity_Init, the retail entity
// initializer.  It preserves the entity's position and render bucket across
// the 0x3AC-byte clear, re-establishes them, sets the identity transform and
// the frame state, clears the seven slot payload words and links the entity
// into its two intrinsic list nodes.
//
// The region is carved out of build_support/layout/units/entity_cacea2.cpp, which owns eight regions, so
// that the one /GL scope that consumes the call can co-compile this body:
// 0x00401110 reaches it twice and retail materialises nothing for the dead
// first argument.  On its own the unit's compile has the same bytes as the
// native-LTCG one, so no cluster is required for this region.
//
// Retail receives the entity in EDX and never reads ECX, so the declaration
// keeps the header's dead leading slot: MSVC assigns the second parameter to
// EDX and the body writes neither incoming register.
//
// The frame state and the two list nodes are written through references to
// their sub-objects rather than through the entity pointer.  Retail's four
// callee-save restores sit at the ends of the frame-state group, the slot
// group, the first node and the function (pop edi/pop esi/pop ebp/pop ebx).
// With plain member stores the pass sinks `pop edi` to the end of the identity
// matrix and stacks `pop ebp` on `pop esi` - a 32-byte delta with the same 67
// instructions.  Going through the sub-object references makes the pass emit
// the restores at retail's four group ends; the machine code of every store is
// unchanged.
#include <string.h>
#include "th10/game/entity.hpp"

#pragma code_seg(".text$00a_init")
__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    Vector3 position = entity->position;
    int32_t bucket = entity->render_bucket;
    memset(entity, 0, sizeof(Entity));
    entity->render_bucket = bucket;
    memcpy(&entity->position, &position, 12);
    entity->primary_color = 0xFFFFFFFF;
    entity->scale_x = 1.0f;
    entity->scale_y = 1.0f;
    Matrix4x4& m = entity->local_transform;
    m.values[3][2] = 0.0f;
    m.values[3][1] = 0.0f;
    m.values[3][0] = 0.0f;
    m.values[2][3] = 0.0f;
    m.values[2][1] = 0.0f;
    m.values[2][0] = 0.0f;
    m.values[1][3] = 0.0f;
    m.values[1][2] = 0.0f;
    m.values[1][0] = 0.0f;
    m.values[0][3] = 0.0f;
    m.values[0][2] = 0.0f;
    m.values[0][1] = 0.0f;
    m.values[3][3] = 1.0f;
    m.values[2][2] = 1.0f;
    m.values[1][1] = 1.0f;
    m.values[0][0] = 1.0f;
    struct FrameState { int32_t previous_frame; int32_t current_frame; float frame_elapsed; };
    entity->end_marker = 7;
    FrameState& frame = *(FrameState*)((char*)entity + 0x5C);
    frame.current_frame = 0;
    frame.previous_frame = 0xFFF0BDC1;
    frame.frame_elapsed = 0.0f;
    entity->pad_0B4[0] = 0;
    entity->pad_100[0] = 0;
    entity->pad_12C[0] = 0;
    entity->pad_178[0] = 0;
    entity->pad_1B4[0] = 0;
    entity->pad_200[0] = 0;
    entity->pad_22C[0] = 0;
    struct EntityLink { Entity* self; void* next; void* prev; };
    EntityLink& animation_node = *(EntityLink*)&entity->manager_node_animation;
    animation_node.self = entity;
    animation_node.next = 0;
    animation_node.prev = 0;
    EntityLink& child_node = *(EntityLink*)&entity->child_node_animation;
    child_node.self = entity;
    child_node.next = 0;
    child_node.prev = 0;
}
