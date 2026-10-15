// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00449530.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimBeginCompilerContext(AnimationNode_00449530** items, int count) {
    while (count--) {
        (*items++)->Begin();
    }
    return 0;
}
#pragma code_seg()
