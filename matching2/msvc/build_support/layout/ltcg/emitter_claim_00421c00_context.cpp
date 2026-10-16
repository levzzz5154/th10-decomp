// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_421c00.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(EmitterSlot** items, int count, int id, int mode, float v) {
    int result = 0;
    while (count--) result += (*items++)->Claim(id, mode, v, v, v, v, v, v, v);
    return result;
}
#pragma code_seg()
