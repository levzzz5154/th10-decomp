// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_421d80.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkCompilerContext(replaybytemark** objects, int count) {
    replaybytemark** cursor = objects;
    while (count--) {
        replaybytemark* object = *cursor++;
        object->Mark();
        object->Mark();
    }
    return 0;
}
#pragma code_seg()
