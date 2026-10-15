// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_0044c140_0044c140.cpp"

#pragma code_seg(".text$03context")
int __stdcall StoreCompilerContext(dwordmark_0044c140** objects, int count) {
    dwordmark_0044c140** cursor = objects;
    while (count--) {
        dwordmark_0044c140* object = *cursor++;
        object->Store();
        object->Store();
    }
    return 0;
}
#pragma code_seg()
