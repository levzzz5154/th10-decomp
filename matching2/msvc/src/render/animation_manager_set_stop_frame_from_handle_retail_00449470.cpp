// 0x00449470 - resolve the animation object behind a handle and set its stop
// frame, propagating the same frame to direct children that are not flagged.
//
// Retail enters this member through the native-LTCG cluster with the handle in
// EAX, the animation id in ECX, and the frame value in SI.  The ordinary C++
// body below remains readable; the synthetic caller in
// layout/ltcg/stop_at_frame_pair_0040c480_context.cpp establishes that private
// register convention.

#include "th10/render/animation_stop_frame_handle.hpp"

struct AnimationLookupContext;

struct AnimationScriptId {
    int value;
};

struct AnimationTreeNode {
    AnimationTreeNode* object;              // +0x000
    AnimationTreeNode* next;                // +0x004
    unsigned char reserved_008[0x0C];
    AnimationTreeNode* children;            // +0x014
    int children_flagged;                   // +0x018
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;              // +0x304
};

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

extern "C" AnimationLookupContext* data_00491c10;

#pragma code_seg(".text$75stop")
void AnimationHandle_00449470::SetStopFrame(unsigned short frame) {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        reinterpret_cast<AnimationManager*>(data_00491c10)->Find(data_00491c10, id));
    if (node != 0) {
        node->stop_frame = frame;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}
#pragma code_seg()
