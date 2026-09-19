// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_anim_setters_00449.cpp"

#pragma code_seg(".text$07context")
int __stdcall AnimationNodeSettersCompilerContext(void** items, int count) {
    int index;
    for (index = 0; index < count; ++index)
        ((AnimationNode_00449*)items[index])->SetStopFrameAndRun();
    for (index = 0; index < count; ++index)
        ((AnimationNode_00449*)items[index])->SetPosition();
    for (index = 0; index < count; ++index)
        ((AnimationNode_00449*)items[index])->SetTranslatedPosition();
    return 0;
}
#pragma code_seg()
