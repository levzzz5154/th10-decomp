#pragma once

// Animation manager view used by the resource-removal marker at 0x004493E0
// and the slot wrapper at 0x0040AE20.

struct AnimationListNode {
    void* object;
    AnimationListNode* next;
};

struct AnimationManager {
    void MarkResourceForRemoval(void* resource);
    void MarkSlotForRemoval(int slot);
};
