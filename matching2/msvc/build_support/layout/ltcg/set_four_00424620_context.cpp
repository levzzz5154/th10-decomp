// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN_00424620_00424620.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(SlotSet** items, int* values, int count) {
    while (count--) (*items++)->SetAll(*values++);
    return 0;
}
#pragma code_seg()
