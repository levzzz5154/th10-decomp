// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_421dc0.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkCompilerContext(replaybytemark5** objects, int count) {
    replaybytemark5** cursor = objects;
    while (count--) {
        replaybytemark5* object = *cursor++;
        object->Mark();
        object->Mark();
    }
    return 0;
}
#pragma code_seg()
