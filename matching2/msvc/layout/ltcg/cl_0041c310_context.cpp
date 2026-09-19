// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0041c310.cpp"
#pragma code_seg(".text$03context")
void __stdcall ReleaseContext_0041c310(OwnedObject_0041c310** objects, int count) {
    for (int index = 0; index < count; ++index) ReleaseOwned_0041c310(objects[index]);
}
#pragma code_seg()
