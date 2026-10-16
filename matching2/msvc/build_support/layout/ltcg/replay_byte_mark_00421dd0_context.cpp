// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_421dd0.cpp"

#pragma code_seg(".text$03context")
int __stdcall MarkCompilerContext(replaybytemark6** objects, int count) {
    replaybytemark6** cursor = objects;
    while (count--) {
        replaybytemark6* object = *cursor++;
        object->Mark();
        object->Mark();
    }
    return 0;
}
#pragma code_seg()
