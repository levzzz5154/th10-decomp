// 0x00449770..0x004497A3: find a script index in the owner's embedded list.
// Return its object's four-byte ID, or zero when no entry matches.
#include <stddef.h>

struct AnimationChildId {
    int value;
    AnimationChildId(int value) : value(value) {}
};
struct IndexedAnimation {
    AnimationChildId id;
    unsigned char reserved_004[0x386];
    short script_index;
};
struct IndexedAnimationLink { IndexedAnimation* object; IndexedAnimationLink* next; IndexedAnimationLink* previous; };
struct EmbeddedAnimationChildren {
    unsigned char reserved_00[0x10];
    IndexedAnimationLink first;
    __declspec(noinline) AnimationChildId __fastcall FindChildId(int index);
};
typedef char EmbeddedChildIdSize[sizeof(AnimationChildId) == 4 ? 1 : -1];
typedef char EmbeddedChildScriptOffset[offsetof(IndexedAnimation, script_index) == 0x38A ? 1 : -1];
typedef char EmbeddedChildLinkSize[sizeof(IndexedAnimationLink) == 12 ? 1 : -1];
typedef char EmbeddedChildHeadOffset[offsetof(EmbeddedAnimationChildren, first) == 0x10 ? 1 : -1];

#pragma code_seg(".text$01find")
AnimationChildId __fastcall EmbeddedAnimationChildren::FindChildId(int index) {
    for (IndexedAnimationLink* node = &first; node; node = node->next)
        if (node->object->script_index == index) return node->object->id;
    return AnimationChildId(0);
}
#pragma code_seg()
