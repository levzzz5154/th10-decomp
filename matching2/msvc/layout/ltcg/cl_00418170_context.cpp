// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00418170.cpp"
#pragma code_seg(".text$03context")
void __stdcall DeletingContext_00418170(OwnedObject_00418170** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_DeletingDestructor_00418170(objects[index], 1);
}
#pragma code_seg()
