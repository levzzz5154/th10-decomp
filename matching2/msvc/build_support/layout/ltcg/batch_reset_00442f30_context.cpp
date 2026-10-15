// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN_00442f30_00442f30.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(QuadBatch_00442f30** items, int count) {
    while (count--) (*items++)->Reset();
    return 0;
}
#pragma code_seg()
