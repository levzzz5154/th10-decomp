// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_42ab80.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_0042ab80(OwnedObject10** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_DeletingDestructor5(objects[index], 1);
}
#pragma code_seg()
