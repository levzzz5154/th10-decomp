// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../contexts/legacy/render/fun.cpp"
#include <string.h>

// ABI anchor (placed at 0x00401DE0, never exported): the landed Entity_Init
// body, mirrored here so the native /LTCG pass can see the callee the
// allocator's heap path calls.  0x00401DE0 takes its entity in EDX with the
// first fastcall slot unread, and no C++ declaration on MSVC 13.10 produces
// that call site - only a visible body makes the pass drop the dead ECX setup.
// The bytes are identical to build_support/contexts/legacy/game/entity_initialize.cpp and must
// stay so; the layout's gap places the section at the retail address, so the
// allocator's own `call 0x401de0` bakes retail's displacement unpatched.
#pragma code_seg(".text$01anchor")
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
#pragma code_seg()

// The manager global the twelve create families load before the call; the
// synthetic loop below keeps it live in ESI across the call exactly as they do.
extern "C" Entity* g_sprt_ctrl_manager;

#pragma code_seg(".text$05context")
int __stdcall AnimationPoolAllocateContext(Entity** output, int count) {
    for (int i = 0; i < count; ++i) {
        AnimationPool* pool = (AnimationPool*)g_sprt_ctrl_manager;
        Entity* entity = pool->Allocate();
        Entity_Init(0, entity);
        output[i] = entity;
    }
    return count;
}
#pragma code_seg()
