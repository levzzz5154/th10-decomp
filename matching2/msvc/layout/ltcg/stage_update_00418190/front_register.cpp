#define data_00491c10 stage_front_data_00491c10
#define data_0047770c stage_front_data_0047770c
#define data_00474c40 stage_front_data_00474c40
#define g_ascii_manager stage_front_data_004776e0
#define data_00477704 stage_front_data_00477704
#define g_player stage_front_data_00477834
#define data_00477838 stage_front_data_00477838
#define data_0047783c stage_front_data_0047783c
#define data_00476f78 stage_front_data_00476f78
#define data_00491fc4 stage_front_data_00491fc4
#define data_00491fb8 stage_front_data_00491fb8
#define data_00492590 stage_front_data_00492590
// 0x004489D0: append an animation to the primary list and assign its nonzero ID.
#include "front_view.hpp"

#pragma code_seg(".text$004489d0_fn")
FrontAnimationId FrontAnimationLists::RegisterPrimaryBack(Entity *object) {
    FrontAnimationListNode *node =
        reinterpret_cast<FrontAnimationListNode *>(&object->manager_node_animation);
    node->object = object;
    node->next = 0;
    node->previous = 0;
    if (!primary_head)
        primary_head = node;
    else {
        FrontAnimationListNode *tail = primary_tail;
        FrontAnimationListNode *next = tail->next;
        if (next) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    primary_tail = node;
    ++next_id;
    if (next_id == FrontAnimationId(0))
        ++next_id;
    object->animation_handle = next_id.value;
    return next_id;
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
