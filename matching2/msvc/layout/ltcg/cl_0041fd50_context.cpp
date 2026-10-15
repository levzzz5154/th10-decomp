// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0041fd50.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_0041fd50(OwnedObject_0041fd50** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_DeletingDestructor_0041fd50(objects[index], 1);
}
#pragma code_seg()
