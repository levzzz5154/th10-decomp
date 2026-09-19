// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00419100.cpp"
#pragma code_seg(".text$03context")
void __stdcall ReleaseContext_00419100(OwnedObject_00419100** objects, int count) {
    for (int index = 0; index < count; ++index) ReleaseOwned_00419100(objects[index]);
}
#pragma code_seg()
