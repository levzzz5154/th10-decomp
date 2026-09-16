// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00421db0_00421db0.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkCompilerContext(replaybytemark_00421db0** objects, int count) {
    replaybytemark_00421db0** cursor = objects;
    while (count--) {
        replaybytemark_00421db0* object = *cursor++;
        object->Mark();
        object->Mark();
    }
    return 0;
}
#pragma code_seg()
