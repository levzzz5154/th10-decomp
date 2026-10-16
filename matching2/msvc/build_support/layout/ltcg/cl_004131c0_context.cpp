// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4131c0.cpp"
#pragma code_seg(".text$03context")
int __stdcall NodeContext_004131c0(Node2** items, int count) {
    while (count--) {
        (*items++)->Remove();
    }
    return 0;
}
#pragma code_seg()
