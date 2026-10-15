// Compiler context only; never selected as recovered game code.
#include "../../src/game/title/heap_destroy_owned_secondary_0042cdb0.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_0042cdb0(OwnedObject_0042cdb0** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_0042cdb0(objects[index]);
}
#pragma code_seg()
