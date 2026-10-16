// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_42a9c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall StoreCompilerContext(dwordmark** objects, int count) {
    dwordmark** cursor = objects;
    while (count--) {
        dwordmark* object = *cursor++;
        object->Store();
        object->Store();
    }
    return 0;
}
#pragma code_seg()
