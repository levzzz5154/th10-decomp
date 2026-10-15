// Complete 0x004497D0 lookup: the four-byte reference has a genuine value constructor.
#include "animation.hpp"
struct SubAnimationChild_004236f0 {
    SubRef4_004236f0 ref;
    unsigned char reserved_004[0x386];
    short script_id;
};
struct SubAnimationChildLink_004236f0 {
    SubAnimationChild_004236f0* object;
    SubAnimationChildLink_004236f0* next;
};
struct SubAnimationNode_004236f0 {
    unsigned char reserved_000[0x10];
    SubAnimationChildLink_004236f0 children;
};
#pragma code_seg(".text$02x")
SubRef4_004236f0 SubHandle4_004236f0::FindChildRef(int script_id) {
    AnimationScriptId id;
    id.value = (int)value;
    SubAnimationNode_004236f0* node = reinterpret_cast<SubAnimationNode_004236f0*>(
        SubAnimFind_004236f0(g_sprt_ctrl, id));
    if (node == 0)
        value = 0;
    for (SubAnimationChildLink_004236f0* link = &node->children; link != 0; link = link->next)
        if (link->object->script_id == script_id)
            return link->object->ref;
    return SubRef4_004236f0(0);
}
#pragma code_seg()
