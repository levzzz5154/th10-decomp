// Compiler context only; its bytes are not recovered game code.
#include "../../src/unreferenced/FUN_0040ae20_0040ae20.cpp"
#include "../../src/core/sprtlib/animation_manager_mark_resource_for_removal_004493e0.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(SprtCtrl** p, int n) {
    for (int i = 0; i < n; ++i) p[i]->MarkSlotForRemoval(i);
}
#pragma code_seg()
