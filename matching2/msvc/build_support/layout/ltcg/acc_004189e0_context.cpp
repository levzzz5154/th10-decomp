// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4189e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_004189e0(ObjectAccessor_004189e0** items, int count) {
    while (count--) {
        (*items++)->ClearState();
    }
    return 0;
}
#pragma code_seg()
