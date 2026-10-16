// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_421d90.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkCompilerContext(replaybytemark2** objects, int count) {
    replaybytemark2** cursor = objects;
    while (count--) {
        replaybytemark2* object = *cursor++;
        object->Mark();
        object->Mark();
    }
    return 0;
}
#pragma code_seg()
