#define g_sprt_ctrl stage_marker_g_sprt_ctrl
#define g_front stage_marker_g_front
#define data_00474c40 stage_marker_data_00474c40
#define g_ascii_manager stage_marker_data_004776e0
#define g_enemy_ctrl stage_marker_g_enemy_ctrl
#define g_player stage_marker_data_00477834
#define data_00477838 stage_marker_data_00477838
#define data_0047783c stage_marker_data_0047783c
#define data_00476f78 stage_marker_data_00476f78
#define data_00491fc4 stage_marker_data_00491fc4
#define data_00491fb8 stage_marker_data_00491fb8
#define data_00492590 stage_marker_data_00492590
// 0x004493E0: mark animation objects that reference a retired script resource.
// The native-LTCG cluster preserves the retail internal EAX/EDX call ABI.

#include "th10/render/animation_resource_removal.hpp"

#ifndef TH10_ANIMATION_RESOURCE_MARK_SECTION
#define TH10_ANIMATION_RESOURCE_MARK_SECTION ".text$20helper"
#endif
#pragma code_seg(".text$004493e0_fn")
__declspec(noinline) void SprtCtrl::MarkResourceForRemoval(void* resource) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);

    AnimationListNode* node = *reinterpret_cast<AnimationListNode**>(
        bytes + 0x72dad4);
    while (node) {
        AnimationListNode* next = node->next;
        unsigned char* object = static_cast<unsigned char*>(node->object);
        if (*reinterpret_cast<void**>(object + 0x308) == resource)
            *reinterpret_cast<unsigned int*>(object + 0x35c) |= 0x04000000u;
        node = next;
    }

    node = *reinterpret_cast<AnimationListNode**>(bytes + 0x72dadc);
    while (node) {
        AnimationListNode* next = node->next;
        unsigned char* object = static_cast<unsigned char*>(node->object);
        if (*reinterpret_cast<void**>(object + 0x308) == resource)
            *reinterpret_cast<unsigned int*>(object + 0x35c) |= 0x04000000u;
        node = next;
    }
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef data_00474c40
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
