// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_4356c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall InstallVtableCompilerContext(FileInterface2** objects, int count) {
    FileInterface2** cursor = objects;
    while (count--) {
        FileInterface2* object = *cursor++;
        object->InstallVtable();
        object->InstallVtable();
    }
    return 0;
}
#pragma code_seg()
