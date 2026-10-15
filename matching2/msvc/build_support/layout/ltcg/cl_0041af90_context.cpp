// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0041af90.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_0041af90(OwnedObject_0041af90** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_DeletingDestructor_0041af90(objects[index], 1);
}
#pragma code_seg()
