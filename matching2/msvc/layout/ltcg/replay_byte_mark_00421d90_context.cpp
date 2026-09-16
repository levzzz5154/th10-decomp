// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00421d90_00421d90.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkCompilerContext(replaybytemark_00421d90** objects, int count) {
    replaybytemark_00421d90** cursor = objects;
    while (count--) {
        replaybytemark_00421d90* object = *cursor++;
        object->Mark();
        object->Mark();
    }
    return 0;
}
#pragma code_seg()
