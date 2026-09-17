// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0041afb0_0041afb0.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_0041afb0(OwnedObject_0041afb0** objects, int count) {
    for (int index = 0; index < count; ++index) DestroyOwned_0041afb0(objects[index]);
}
#pragma code_seg()
