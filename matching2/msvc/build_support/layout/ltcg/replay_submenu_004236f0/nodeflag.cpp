// 0x00449590/0x004495E0: raise or clear flag bit 1 on the node named by the
// object's first field and on its child chain when it has no children.
#include "animation.hpp"
#pragma code_seg(".text$02t")
void SubAnimNode::SetFlag() {
    AnimationScriptId id;
    id.value = (int)field_000;
    SubAnimNode* node = reinterpret_cast<SubAnimNode*>(
        SubAnimFind_004236f0(g_sprt_ctrl, id));
    if (node == 0) {
        return;
    }
    node->flags_35c |= 2;
    if (node->field_018 != 0) {
        return;
    }
    for (SubAnimNode* child = node->field_014; child != 0; child = child->field_004) {
        child->field_000->flags_35c |= 2;
    }
}
#pragma code_seg()
#pragma code_seg(".text$02v")
void SubAnimNode::ClearFlag() {
    AnimationScriptId id;
    id.value = (int)field_000;
    SubAnimNode* node = reinterpret_cast<SubAnimNode*>(
        SubAnimFind_004236f0(g_sprt_ctrl, id));
    if (node == 0) {
        return;
    }
    node->flags_35c &= ~2u;
    if (node->field_018 != 0) {
        return;
    }
    for (SubAnimNode* child = node->field_014; child != 0; child = child->field_004) {
        child->field_000->flags_35c &= ~2u;
    }
}
#pragma code_seg()
