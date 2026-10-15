// Complete 0x00409E50 stop-frame-1 propagation.
#include "th10/game/pause_choice_00422c80/animation.hpp"
#include "th10/game/pause_choice_00422c80/tree.hpp"
#pragma code_seg(".text$06stop1")
void Handle4::StopAtFrame1() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        AnimationManager_Find(g_sprt_ctrl, id));
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
