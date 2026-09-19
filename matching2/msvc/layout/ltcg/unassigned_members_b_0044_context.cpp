// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_members_b_0044.cpp"

#pragma code_seg(".text$15context")
int __stdcall UnassignedMembersBCompilerContext(void** items, int count) {
    int index;
    for (index = 0; index < count; ++index)
        ((UnassignedData_0044bff0*)items[index])->Value();
    for (index = 0; index < count; ++index)
        ((UnassignedScale_0044c5f0*)items[index])->Scaled(1.0f);
    for (index = 0; index < count; ++index)
        ((UnassignedVector_004452a0*)items[index])->Length();
    for (index = 0; index < count; ++index)
        ((UnassignedSpan_00443680*)items[index])->Transform(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
    for (index = 0; index < count; ++index)
        ((UnassignedClear_0044dbb0*)items[index])->Clear();
    for (index = 0; index < count; ++index)
        ((UnassignedHandle_0044c240*)items[index])->Close();
    for (index = 0; index < count; ++index)
        ((UnassignedChain_0044c6b0*)items[index])->Find(0x11);
    for (index = 0; index < count; ++index)
        ((UnassignedSeat_0044c6d0*)items[index])->Bind(0x22);
    for (index = 0; index < count; ++index)
        ((UnassignedBlock_00442010*)items[index])->Reset();
    for (index = 0; index < count; ++index)
        ((UnassignedBlock_004421e0*)items[index])->Reset();
    return 0;
}
#pragma code_seg()
