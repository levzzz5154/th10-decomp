// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_421df0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearCompilerContext(ReplaySlotClearB** objects, int count) {
    ReplaySlotClearB** cursor = objects;
    while (count--) {
        ReplaySlotClearB* object = *cursor++;
        object->Clear();
        object->Clear();
    }
    return 0;
}
#pragma code_seg()
