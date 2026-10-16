// Synthetic compiler context only.
#include "../../../src/unreferenced/FUN.cpp_40b1b0.cpp"
#include "animation_public_callers_anchors.cpp"
#pragma code_seg(".text$17context")
extern "C" int __stdcall AnimationPublicCallersContext(void** resources, void*** outputs,
        int* indexes, const AnimationPosition** positions,
        TitleEffectState** states, int count,
        AnimationInitializer initialize, AnimationCallback update,
        AnimationCallback draw) {
    for (int i=0; i<count; ++i) {
        AnimationScriptId script = {indexes[i]};
        AnimationCreateWithCallbacks2((AnimationScriptId*)outputs[i],
            (AnimationBank*)resources[i],script,states[i],initialize,update,draw);
        TitleEffectsAdvance(states[i]);
        AnimationManager_CreatePositionedPrimary(resources[i], outputs[i], indexes[i], positions[i]);
    }
    return count;
}
#pragma code_seg()
