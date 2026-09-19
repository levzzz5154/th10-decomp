// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_004148c0.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_004148c0(OwnedObject_004148c0** objects, int count) {
    for (int index = 0; index < count; ++index) ReleaseComposite_DeletingDestructor_004148c0(objects[index], 1);
}
#pragma code_seg()
