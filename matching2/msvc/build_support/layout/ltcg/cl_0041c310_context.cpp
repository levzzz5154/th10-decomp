// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41c310.cpp"
#pragma code_seg(".text$03context")
void __stdcall ReleaseContext_0041c310(OwnedObject7** objects, int count) {
    for (int index = 0; index < count; ++index) ReleaseOwned3(objects[index]);
}
#pragma code_seg()
