// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_0043a490_0043a490.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearCompilerContext(SoundPairClear_0043a490** objects, int count) {
    SoundPairClear_0043a490** cursor = objects;
    while (count--) {
        SoundPairClear_0043a490* object = *cursor++;
        object->Clear();
        object->Clear();
    }
    return 0;
}
#pragma code_seg()
