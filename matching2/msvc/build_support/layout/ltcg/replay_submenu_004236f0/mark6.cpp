// Complete 0x004243F0 stop-frame-6 propagation on the returned reference.
#include "animation.hpp"
#pragma code_seg(".text$02j")
void SubRef4::StopAtFrame6() {
    AnimationScriptId id;
    id.value = value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        SubAnimFind_004236f0(g_sprt_ctrl, id));
    if (node != 0) {
        node->stop_frame = 6;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 6;
        }
    }
}
#pragma code_seg()
