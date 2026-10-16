// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_421de0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearCompilerContext(ReplaySlotClearA** objects, int count) {
    ReplaySlotClearA** cursor = objects;
    while (count--) {
        ReplaySlotClearA* object = *cursor++;
        object->Clear();
        object->Clear();
    }
    return 0;
}
#pragma code_seg()
