// 0x00401DE0..0x00401EF0 (273 bytes): compiler-context copy of Entity_Init for
// the animation-storage constructor cluster.  No bytes are selected from it.
//
// It is defined `inline` here, as a header-inline (COMDAT) function: retail
// callers never rely on EDX surviving the call although the body preserves it
// (the constructor's pool loop reloads `mov edx,edi` on every iteration and
// keeps its counter in memory).  With an out-of-line `noinline` definition
// LTCG keeps the pool pointer in EDX across the call; the inline definition
// has the same 273 bytes and the same EDX argument, but its callers assume the
// scratch registers are lost.
#include <string.h>
#include "th10/game/entity.hpp"

#pragma code_seg(".text$00a_init")
inline void __fastcall Entity_Init(void* unused, Entity* entity) {
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
