// Synthetic compiler context only.
#include "../../src/unidentified/FUN_0040b1b0_0040b1b0.cpp"
#include "animation_public_callers_anchors.cpp"
#pragma code_seg(".text$17context")
extern "C" int __stdcall AnimationPublicCallersContext(void** resources, void*** outputs,
        int* indexes, const AnimationPosition_00448d50** positions,
        TitleEffectState_0041fdd0** states, int count,
        AnimationInitializer_0040b1b0 initialize, AnimationCallback_0040b1b0 update,
        AnimationCallback_0040b1b0 draw) {
    for (int i=0; i<count; ++i) {
        AnimationScriptId script = {indexes[i]};
        AnimationCreateWithCallbacks_0040b1b0((AnimationScriptId*)outputs[i],
            (AnimationResource_00449870*)resources[i],script,states[i],initialize,update,draw);
        TitleEffectsAdvance_0041fdd0(states[i]);
        AnimationManager_CreatePositionedPrimary_00448d50(resources[i], outputs[i], indexes[i], positions[i]);
    }
    return count;
}
#pragma code_seg()
