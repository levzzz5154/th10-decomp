// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_44c140.cpp"

#pragma code_seg(".text$03context")
int __stdcall StoreCompilerContext(dwordmark2** objects, int count) {
    dwordmark2** cursor = objects;
    while (count--) {
        dwordmark2* object = *cursor++;
        object->Store();
        object->Store();
    }
    return 0;
}
#pragma code_seg()
