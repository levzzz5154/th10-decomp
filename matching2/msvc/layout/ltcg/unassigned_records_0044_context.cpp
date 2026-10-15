// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_records_0044.cpp"

#pragma code_seg(".text$07context")
int __stdcall UnassignedRecordsCompilerContext(void** items, void** others, int count) {
    int index;
    for (index = 0; index < count; ++index)
        ((UnassignedTriple_00442130*)items[index])->CopyInto((UnassignedHolder_00442130*)items[index]);
    for (index = 0; index < count; ++index)
        ((UnassignedTriple_00442150*)items[index])->CopyInto((UnassignedHolder_00442150*)items[index]);
    for (index = 0; index < count; ++index)
        ((UnassignedTriple_004421c0*)items[index])->CopyInto((UnassignedHolder_004421c0*)items[index]);
    for (index = 0; index < count; ++index)
    return 0;
}
#pragma code_seg()
