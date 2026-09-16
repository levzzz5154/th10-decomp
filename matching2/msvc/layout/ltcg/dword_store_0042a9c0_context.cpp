// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0042a9c0_0042a9c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall StoreCompilerContext(dwordmark_0042a9c0** objects, int count) {
    dwordmark_0042a9c0** cursor = objects;
    while (count--) {
        dwordmark_0042a9c0* object = *cursor++;
        object->Store();
        object->Store();
    }
    return 0;
}
#pragma code_seg()
