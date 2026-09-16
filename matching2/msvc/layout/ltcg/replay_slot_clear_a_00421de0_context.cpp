// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00421de0_00421de0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearCompilerContext(ReplaySlotClearA_00421de0** objects, int count) {
    ReplaySlotClearA_00421de0** cursor = objects;
    while (count--) {
        ReplaySlotClearA_00421de0* object = *cursor++;
        object->Clear();
        object->Clear();
    }
    return 0;
}
#pragma code_seg()
