#define data_00491c10 stage_front_data_00491c10
#define data_0047770c stage_front_data_0047770c
#define data_00474c40 stage_front_data_00474c40
#define data_004776e0 stage_front_data_004776e0
#define data_00477704 stage_front_data_00477704
#define data_00477834 stage_front_data_00477834
#define data_00477838 stage_front_data_00477838
#define data_0047783c stage_front_data_0047783c
#define data_00476f78 stage_front_data_00476f78
#define data_00491fc4 stage_front_data_00491fc4
#define data_00491fb8 stage_front_data_00491fb8
#define data_00492590 stage_front_data_00492590
#include <string.h>
#include "front_view.hpp"

#pragma code_seg(".text$00401de0_fn")
__declspec(noinline) void __stdcall Entity_Init(Entity *entity) {
    Vector3 position = entity->position;
    int32_t bucket = entity->render_bucket;
    memset(entity, 0, sizeof(Entity));
    entity->render_bucket = bucket;
    memcpy(&entity->position, &position, 12);
    entity->primary_color = 0xFFFFFFFF;
    entity->scale_x = 1.0f;
    entity->scale_y = 1.0f;
    Matrix4x4 &m = entity->local_transform;
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
    struct FrameState {
        int32_t previous_frame;
        int32_t current_frame;
        float frame_elapsed;
    };
    entity->end_marker = 7;
    FrameState &frame = *(FrameState *)((char *)entity + 0x5C);
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
    struct EntityLink {
        Entity *self;
        void *next;
        void *prev;
    };
    EntityLink &animation_node = *(EntityLink *)&entity->manager_node_animation;
    animation_node.self = entity;
    animation_node.next = 0;
    animation_node.prev = 0;
    EntityLink &child_node = *(EntityLink *)&entity->child_node_animation;
    child_node.self = entity;
    child_node.next = 0;
    child_node.prev = 0;
}

#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef data_00477834
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
