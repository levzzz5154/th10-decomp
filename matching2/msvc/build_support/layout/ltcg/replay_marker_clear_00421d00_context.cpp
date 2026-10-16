// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_421d00.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearCompilerContext(ReplayMarkerClear** objects, int count) {
    ReplayMarkerClear** cursor = objects;
    while (count--) {
        ReplayMarkerClear* object = *cursor++;
        object->Clear();
        object->Clear();
    }
    return 0;
}
#pragma code_seg()
