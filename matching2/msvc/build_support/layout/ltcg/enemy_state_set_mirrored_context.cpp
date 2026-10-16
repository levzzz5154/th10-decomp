// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_40cde0.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetMirroredCompilerContext(EnemyState2** objects, int count) {
    EnemyState2** cursor = objects;
    while (count--) {
        EnemyState2* object = *cursor++;
        object->SetMirrored();
        object->SetMirrored();
    }
    return 0;
}
#pragma code_seg()
