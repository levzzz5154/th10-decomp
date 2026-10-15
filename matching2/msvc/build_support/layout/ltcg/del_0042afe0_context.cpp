// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0042afe0.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_0042afe0(OwnedObject_0042afe0** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_DeletingDestructor_0042afe0(objects[index], 1);
}
#pragma code_seg()
