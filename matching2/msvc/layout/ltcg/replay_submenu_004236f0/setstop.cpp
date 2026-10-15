// Complete 0x00449470 variable stop-frame propagation.
#include "animation.hpp"
#pragma code_seg(".text$02r")
void SubHandle4_004236f0::SetStopFrame(short frame) {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        SubAnimFind_004236f0(g_sprt_ctrl, id));
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
