// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_clear_flag_004495e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimFlagCompilerContext(AnimationNode_004495e0** items, int count) {
    while (count--) {
        (*items++)->ClearFlag();
    }
    return 0;
}
#pragma code_seg()
