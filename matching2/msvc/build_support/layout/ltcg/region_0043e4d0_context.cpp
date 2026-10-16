// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_43e4d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall HolderCompilerContext(Holder3** items, int count, float seconds) {
    while (count--) {
        (*items++)->SetSeconds(seconds);
    }
    return 0;
}
#pragma code_seg()
