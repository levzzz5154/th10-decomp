// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_0040cde0_0040cde0.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetMirroredCompilerContext(EnemyState_0040cde0** objects, int count) {
    EnemyState_0040cde0** cursor = objects;
    while (count--) {
        EnemyState_0040cde0* object = *cursor++;
        object->SetMirrored();
        object->SetMirrored();
    }
    return 0;
}
#pragma code_seg()
