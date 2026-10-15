// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtlib/animation_manager_set_flag_bit1_00449590.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimFlagCompilerContext(AnimationNode_00449590** items, int count) {
    while (count--) {
        (*items++)->SetFlag();
    }
    return 0;
}
#pragma code_seg()
