// Compiler context only; never selected as recovered game code.
#include "../../src/core/sprtlib/animation_manager_mark_for_removal_and_clear_handle_00449630.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkForRemovalContext_00449630(AnimationHandle_00449630* handles, int count,
                                             SprtCtrl* manager) {
    for (int i = 0; i < count; ++i)
        handles[i].MarkForRemovalAndClear(manager);
    return 0;
}
#pragma code_seg()
