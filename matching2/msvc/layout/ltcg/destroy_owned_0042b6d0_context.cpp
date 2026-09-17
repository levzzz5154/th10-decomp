// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0042b6d0_0042b6d0.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_0042b6d0(OwnedObject_0042b6d0** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_0042b6d0(objects[index]);
}
#pragma code_seg()
