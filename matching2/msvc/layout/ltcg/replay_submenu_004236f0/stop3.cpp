// Complete 0x0040C4D0: stop frame 3 propagation; the 0x0040C480 pair model
// with the frame fixed.
#include "animation.hpp"
#pragma code_seg(".text$02b")
void SubHandle4_004236f0::StopAtFrame3() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        SubAnimFind_004236f0(g_sprt_ctrl, id));
    if (node != 0) {
        node->stop_frame = 3;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 3;
        }
    }
}
#pragma code_seg()
