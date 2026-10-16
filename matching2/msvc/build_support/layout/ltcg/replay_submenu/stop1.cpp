// Complete 0x00409E50: stop frame 1 propagation (used by the timed-state
// reset when the result screen tears its animations down).
#include "animation.hpp"
#pragma code_seg(".text$00d")
void SubHandle4::StopAtFrame1() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        SubAnimFind_004236f0(g_sprt_ctrl, id));
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
