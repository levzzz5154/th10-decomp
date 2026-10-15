// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00421d80_00421d80.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkCompilerContext(replaybytemark_00421d80** objects, int count) {
    replaybytemark_00421d80** cursor = objects;
    while (count--) {
        replaybytemark_00421d80* object = *cursor++;
        object->Mark();
        object->Mark();
    }
    return 0;
}
#pragma code_seg()
