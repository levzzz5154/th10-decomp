// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00425090_00425090.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_00425090(OwnedObject_00425090** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_00425090(objects[index]);
}
#pragma code_seg()
