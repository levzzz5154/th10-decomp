#include "th10/game/pause_initializer_00422ab0.hpp"
#pragma code_seg(".text$03stop")
void Handle4::StopAtFrame3() {
    AnimationScriptId id; id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(AnimationManager_Find_004491c0(data_00491c10, id));
    if (node != 0) {
        node->stop_frame = 3;
        if (!node->children_flagged)
            for (AnimationTreeNode* child=node->children; child != 0; child=child->next)
                child->object->stop_frame = 3;
    }
}
#pragma code_seg()
