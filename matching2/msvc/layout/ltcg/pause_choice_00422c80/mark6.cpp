// Complete 0x004243F0 stop-frame-6 propagation on the returned reference.
#include "th10/game/pause_choice_00422c80/animation.hpp"
#include "th10/game/pause_choice_00422c80/tree.hpp"
#pragma code_seg(".text$40mark6")
void Ref4::StopAtFrame6() {
    AnimationScriptId id;
    id.value = value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        AnimationManager_Find_004491c0(data_00491c10, id));
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
