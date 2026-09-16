// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00421d00_00421d00.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearCompilerContext(ReplayMarkerClear_00421d00** objects, int count) {
    ReplayMarkerClear_00421d00** cursor = objects;
    while (count--) {
        ReplayMarkerClear_00421d00* object = *cursor++;
        object->Clear();
        object->Clear();
    }
    return 0;
}
#pragma code_seg()
