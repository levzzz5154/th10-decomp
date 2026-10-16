// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41f820.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_0041f820(ObjectAccessor_0041f820** items, int count) {
    while (count--) {
        (*items++)->UpdateFlag();
    }
    return 0;
}
#pragma code_seg()
