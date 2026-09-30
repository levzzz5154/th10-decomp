// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_00421c00.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(EmitterSlot_00421c00** items, int count, int id, int mode, float v) {
    int result = 0;
    while (count--) result += (*items++)->Claim(id, mode, v, v, v, v, v, v, v);
    return result;
}
#pragma code_seg()
