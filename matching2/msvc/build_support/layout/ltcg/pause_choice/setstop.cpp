// Complete 0x00449470 variable stop-frame propagation.
#include "th10/game/pause_choice/animation.hpp"
#include "th10/game/pause_choice/tree.hpp"
#pragma code_seg(".text$60setstop")
void Handle4::SetStopFrame(short frame) {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        AnimationManager_Find(g_sprt_ctrl, id));
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
