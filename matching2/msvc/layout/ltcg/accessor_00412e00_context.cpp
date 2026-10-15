// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00412e00_00412e00.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearCompilerContext(ObjectAccessor_00412e00** objects, int count) {
    ObjectAccessor_00412e00** cursor = objects;
    while (count--) {
        ObjectAccessor_00412e00* object = *cursor++;
        object->Clear();
        object->Clear();
    }
    return 0;
}
#pragma code_seg()
