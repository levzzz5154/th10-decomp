// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4148c0.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_004148c0(OwnedObject** objects, int count) {
    for (int index = 0; index < count; ++index) ReleaseComposite_DeletingDestructor(objects[index], 1);
}
#pragma code_seg()
