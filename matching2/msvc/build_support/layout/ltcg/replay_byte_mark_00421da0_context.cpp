// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_421da0.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkCompilerContext(replaybytemark3** objects, int count) {
    replaybytemark3** cursor = objects;
    while (count--) {
        replaybytemark3* object = *cursor++;
        object->Mark();
        object->Mark();
    }
    return 0;
}
#pragma code_seg()
