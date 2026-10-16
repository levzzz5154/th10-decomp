// Compiler context only; never selected as recovered game code.
#include "../../../src/game/fps/animation_set_active_count.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimationSetActiveCountCompilerContext(AnimationManager4** managers,
                                                     int count) {
    for (int index = 0; index < count; ++index)
        managers[index]->SetActiveCount(count);
    return 0;
}
#pragma code_seg()
