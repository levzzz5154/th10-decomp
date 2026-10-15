// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_members_0044.cpp"

#pragma code_seg(".text$50context")
int __stdcall UnassignedMembersCompilerContext(void** items, int count) {
    int index;
    for (index = 0; index < count; ++index)
        ((UnassignedFlagged_004452e0*)items[index])->LowBit();
    for (index = 0; index < count; ++index)
        ((UnassignedMasked_0044bf20*)items[index])->ClearLowBit();
    for (index = 0; index < count; ++index)
        ((UnassignedMarked_0044c250*)items[index])->MarkBit1();
    for (index = 0; index < count; ++index)
        ((UnassignedRef_0044c600*)items[index])->Release();
    for (index = 0; index < count; ++index)
        ((UnassignedAttach_0044c640*)items[index])->AttachSelf();
    for (index = 0; index < count; ++index)
        ((UnassignedZero_0044c760*)items[index])->Reset();
    return 0;
}
#pragma code_seg()
