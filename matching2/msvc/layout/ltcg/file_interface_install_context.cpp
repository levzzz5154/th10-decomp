// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_004356c0_004356c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall InstallVtableCompilerContext(FileInterface_004356c0** objects, int count) {
    FileInterface_004356c0** cursor = objects;
    while (count--) {
        FileInterface_004356c0* object = *cursor++;
        object->InstallVtable();
        object->InstallVtable();
    }
    return 0;
}
#pragma code_seg()
