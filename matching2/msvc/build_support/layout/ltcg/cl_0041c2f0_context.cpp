// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0041c2f0.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_0041c2f0(OwnedObject_0041c2f0** objects, int count) {
    for (int index = 0; index < count; ++index) ScoreExtendedObject_Destroy_DeletingDestructor(objects[index], 1);
}
#pragma code_seg()
