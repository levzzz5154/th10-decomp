#include "hud_view.hpp"
__declspec(noinline) void* __fastcall ResultAnimation_Find(ResultAnimationLookup*,ResultAnimationId);
#define data_00491c10 stage_handle_data_00491c10
#define data_0047770c stage_handle_data_0047770c
#define data_00474c40 stage_handle_data_00474c40
#define data_004776e0 stage_handle_data_004776e0
#define data_00477704 stage_handle_data_00477704
#define data_00477834 stage_handle_data_00477834
#define data_00477838 stage_handle_data_00477838
#define data_0047783c stage_handle_data_0047783c
#define data_00476f78 stage_handle_data_00476f78
#define data_00491fc4 stage_handle_data_00491fc4
#define data_00491fb8 stage_handle_data_00491fb8
#define data_00492590 stage_handle_data_00492590
// 0x00409E50 - resolve the animation object behind an animation handle and set
// its sprite word to 1, propagating that value to the object's direct children
// unless the object is already flagged as having processed them.
//
// The handle is the receiver and the only input: retail's callers put its
// address in EAX and nothing else, and the animation lookup never reads its own
// receiver, so the whole-program pass leaves EAX holding the dereferenced
// pointer and hands the lookup's id back on the stack.  Both are conventions
// only a native-LTCG cluster reaches; this unit is co-compiled with the
// StopAtFrame pair that owns 0x004491C0 (layout/ltcg/stop_at_frame_pair_0040c480.json).

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




extern "C" AnimationLookupContext* data_00491c10;

#pragma code_seg(".text$00409e50_fn")
void AnimationHandle::StopAtFrame1() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        ResultAnimation_Find(data_00491c10, id));
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
