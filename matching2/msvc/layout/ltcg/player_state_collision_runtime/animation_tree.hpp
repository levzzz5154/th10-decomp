#pragma once
// The child list of an animation, as the handle helpers walk it.
struct MovementChildNode {
    Entity* object;
    MovementChildNode* next;
};
struct MovementAnimationTree {
    unsigned char reserved_000[0x14];
    MovementChildNode* children;
    int children_flagged;
};
