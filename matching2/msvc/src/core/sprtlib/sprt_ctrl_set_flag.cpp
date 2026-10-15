#include "th10/source_views/animation_manager_12b25f_0.hpp"
#include "th10/source_views/animation_manager_12b25f_1.hpp"
void* __fastcall SprtCtrl::SetFlag(AnimationLookupContext* context, int id) {
    // The lookup is the sibling entry point; the retail call keeps the manager
    // object in ECX and the context in EDX, so it goes through its fixed address.
    AnimationLookupEntry* entry = (AnimationLookupEntry*)
        ((AnimationFindFn)asm_AnimationManager_Find_004491c0)(this, context, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
    return entry;
}
