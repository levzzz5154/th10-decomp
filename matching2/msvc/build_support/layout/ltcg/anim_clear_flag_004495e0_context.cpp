// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtlib/animation_manager_clear_flag.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimFlagCompilerContext(AnimationNode11** items, int count) {
    while (count--) {
        (*items++)->ClearFlag();
    }
    return 0;
}
#pragma code_seg()
