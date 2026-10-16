// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_419100.cpp"
#pragma code_seg(".text$03context")
void __stdcall ReleaseContext_00419100(OwnedObject4** objects, int count) {
    for (int index = 0; index < count; ++index) ReleaseOwned2(objects[index]);
}
#pragma code_seg()
