#define g_sprt_ctrl stage_front_g_sprt_ctrl
#define g_front stage_front_g_front
#define g_globals stage_front_data_00474c40
#define g_ascii_manager stage_front_data_004776e0
#define g_enemy_ctrl stage_front_g_enemy_ctrl
#define g_player stage_front_data_00477834
#define g_replay stage_front_data_00477838
#define g_score stage_front_data_0047783c
#define g_game_speed stage_front_data_00476f78
#define data_00491fc4 stage_front_data_00491fc4
#define data_00491fb8 stage_front_data_00491fb8
#define g_sound_manager stage_front_data_00492590
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
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef data_00491fc4
#undef data_00491fb8
#undef g_sound_manager
