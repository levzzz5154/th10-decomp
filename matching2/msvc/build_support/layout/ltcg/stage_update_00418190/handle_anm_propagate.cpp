#include "hud_view.hpp"
__declspec(noinline) void* __fastcall ResultAnimation_Find(ResultAnimationLookup*,ResultAnimationId);
#define g_sprt_ctrl stage_handle_g_sprt_ctrl
#define g_front stage_handle_g_front
#define g_globals stage_handle_data_00474c40
#define g_ascii_manager stage_handle_data_004776e0
#define g_enemy_ctrl stage_handle_g_enemy_ctrl
#define g_player stage_handle_data_00477834
#define g_replay stage_handle_data_00477838
#define g_score stage_handle_data_0047783c
#define g_game_speed stage_handle_data_00476f78
#define g_stage_flags stage_handle_data_00491fc4
#define g_main_state stage_handle_data_00491fb8
#define g_sound_manager stage_handle_data_00492590
// 0x00409E50 - resolve the animation object behind an animation handle and set
// its sprite word to 1, propagating that value to the object's direct children
// unless the object is already flagged as having processed them.
//
// The handle is the receiver and the only input: retail's callers put its
// address in EAX and nothing else, and the animation lookup never reads its own
// receiver, so the whole-program pass leaves EAX holding the dereferenced
// pointer and hands the lookup's id back on the stack.  Both are conventions
// only a native-LTCG cluster reaches; this unit is co-compiled with the
// StopAtFrame pair that owns 0x004491C0 (build_support/layout/ltcg/stop_at_frame_pair_0040c480.json).

#include "th10/render/animation_handle.hpp"

typedef ResultAnimationLookup AnimationLookupContext;

// The script id is a four-byte record so the lookup reads it from its stack
// slot; see the note in animation_manager_find_004491c0.cpp.
typedef ResultAnimationId AnimationScriptId;

struct AnimationTreeNode {
    AnimationTreeNode* object;              // +0x000
    AnimationTreeNode* next;                // +0x004
    unsigned char reserved_008[0x0C];
    AnimationTreeNode* children;            // +0x014
    int children_flagged;                   // +0x018
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;              // +0x304
};




extern "C" AnimationLookupContext* g_sprt_ctrl;

#pragma code_seg(".text$00409e50_fn")
void AnimationHandle::StopAtFrame1() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        ResultAnimation_Find(g_sprt_ctrl, id));
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
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
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager
