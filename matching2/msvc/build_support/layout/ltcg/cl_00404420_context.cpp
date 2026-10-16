// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_404420.cpp"

#include "animation_lookup_anchors.cpp"

#pragma code_seg(".text$06context")
int __stdcall ReleaseAnimationsContext_00404420(AnimationPairOwner* owners, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i)
        owners[i].ReleaseAnimations();
    return result;
}
#pragma code_seg()
