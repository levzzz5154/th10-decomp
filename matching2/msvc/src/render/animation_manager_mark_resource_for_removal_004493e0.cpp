// 0x004493E0: mark animation objects that reference a retired script resource.
// The native-LTCG cluster preserves the retail internal EAX/EDX call ABI.

#include "th10/render/animation_resource_removal.hpp"

#ifndef TH10_ANIMATION_RESOURCE_MARK_SECTION
#define TH10_ANIMATION_RESOURCE_MARK_SECTION ".text$20helper"
#endif
#pragma code_seg(TH10_ANIMATION_RESOURCE_MARK_SECTION)
__declspec(noinline) void AnimationManager::MarkResourceForRemoval(void* resource) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);

    AnimationListNode* node = *reinterpret_cast<AnimationListNode**>(
        bytes + 0x72dad4);
    while (node) {
        AnimationListNode* next = node->next;
        unsigned char* object = static_cast<unsigned char*>(node->object);
        if (*reinterpret_cast<void**>(object + 0x308) == resource)
            *reinterpret_cast<unsigned int*>(object + 0x35c) |= 0x04000000u;
        node = next;
    }

    node = *reinterpret_cast<AnimationListNode**>(bytes + 0x72dadc);
    while (node) {
        AnimationListNode* next = node->next;
        unsigned char* object = static_cast<unsigned char*>(node->object);
        if (*reinterpret_cast<void**>(object + 0x308) == resource)
            *reinterpret_cast<unsigned int*>(object + 0x35c) |= 0x04000000u;
        node = next;
    }
}
#pragma code_seg()
