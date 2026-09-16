// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00421df0_00421df0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearCompilerContext(ReplaySlotClearB_00421df0** objects, int count) {
    ReplaySlotClearB_00421df0** cursor = objects;
    while (count--) {
        ReplaySlotClearB_00421df0* object = *cursor++;
        object->Clear();
        object->Clear();
    }
    return 0;
}
#pragma code_seg()
