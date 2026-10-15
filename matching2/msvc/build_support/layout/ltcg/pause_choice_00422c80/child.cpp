// Complete 0x004497D0 lookup: the four-byte reference has a genuine value constructor.
#include "th10/game/pause_choice_00422c80/animation.hpp"
struct AnimationChild_004497d0 {
    Ref4 ref;
    unsigned char reserved_004[0x386];
    short script_id;
};
struct AnimationChildLink_004497d0 {
    AnimationChild_004497d0* object;
    AnimationChildLink_004497d0* next;
};
struct AnimationNode_004497d0 {
    unsigned char reserved_000[0x10];
    AnimationChildLink_004497d0 children;
};
#pragma code_seg(".text$70child")
Ref4 Handle4::FindChildRef(int script_id) {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationNode_004497d0* node = reinterpret_cast<AnimationNode_004497d0*>(
        AnimationManager_Find(g_sprt_ctrl, id));
    if (node == 0)
        value = 0;
    for (AnimationChildLink_004497d0* link = &node->children; link != 0; link = link->next)
        if (link->object->script_id == script_id)
            return link->object->ref;
    return Ref4(0);
}
#pragma code_seg()
