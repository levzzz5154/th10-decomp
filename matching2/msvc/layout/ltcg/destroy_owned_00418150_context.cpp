// Compiler context only; never selected as recovered game code.
#include "../../src/game/game/heap_destroy_owned_00418150.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_00418150(OwnedObject_00418150** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_00418150(objects[index]);
}
#pragma code_seg()
