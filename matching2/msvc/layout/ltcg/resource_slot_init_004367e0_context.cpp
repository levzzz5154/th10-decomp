// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_004367e0_004367e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall InitCompilerContext(ResourceSlotInit_004367e0** items, int count, int value) {
    while (count--) {
        (*items++)->Init(value);
    }
    return 0;
}
#pragma code_seg()
