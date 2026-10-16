// 0x004495E0, which clears the hidden flag of the animation a handle names
// and of its direct children, as the shot type selection screen 0x00430A60
// calls it: unselected here and sharing the one lookup at 0x004491C0 of this
// link (the maintained form is src/core/sprtlib/animation_manager_clear_flag.cpp).
#include "th10/game/shot_type_select_update.hpp"
struct AnimationNode11 {
    AnimationNode11* object;             // +0x000
    AnimationNode11* next;               // +0x004
    unsigned char reserved_008[0x0C];
    AnimationNode11* children;           // +0x014
    AnimationNode11* children_flagged;   // +0x018
    unsigned char reserved_01c[0x340];
    unsigned int flags;                         // +0x35C
};
#pragma code_seg(".text$004495e0_fn")
void AnimationHandle12::ClearFlag() {
    AnimationNode11* node = reinterpret_cast<AnimationNode11*>(
        reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(
            reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), id));
    if (node == 0) return;
    node->flags &= ~2u;
    if (node->children_flagged != 0) return;
    for (AnimationNode11* child = node->children; child != 0; child = child->next)
        child->object->flags &= ~2u;
}
#pragma code_seg()
