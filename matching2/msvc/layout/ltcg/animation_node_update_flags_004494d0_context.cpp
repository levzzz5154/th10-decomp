// Synthetic compiler context only; not recovered game behavior.  The array
// call shape is intended to expose the receiver in EAX as observed at retail.
#include "../../src/unreferenced/unassigned_004494d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimUpdateFlagsFromLookupCompilerContext(
        AnimationNode_004494D0** items, int count) {
    while (count--) {
        (*items++)->UpdateFlags();
    }
    return 0;
}
#pragma code_seg()
