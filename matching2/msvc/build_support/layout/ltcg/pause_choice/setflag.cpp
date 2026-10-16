// Complete 0x004492A0: mark this animation and its direct children for transition.
#include "th10/game/pause_choice/animation.hpp"
struct AnimationFlagEntry {
    AnimationFlagEntry* object;
    AnimationFlagEntry* next;
    unsigned char reserved_08[0x0C];
    AnimationFlagEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x340];
    unsigned int flags;
};
#pragma code_seg(".text$55setflag")
void* __fastcall AnimationManager_SetFlag2(
        AnimationLookupContext* context, AnimationScriptId id) {
    AnimationFlagEntry* entry = (AnimationFlagEntry*)AnimationManager_Find(context, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
    return entry;
}
#pragma code_seg()
