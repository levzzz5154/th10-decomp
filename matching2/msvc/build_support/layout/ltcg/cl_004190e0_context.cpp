// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4190e0.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_004190e0(OwnedObject3** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_DeletingDestructor2(objects[index], 1);
}
#pragma code_seg()
