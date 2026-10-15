// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_0044c620_0044c620.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResetCompilerContext(CameraPairReset** objects, int count) {
    CameraPairReset** cursor = objects;
    while (count--) {
        CameraPairReset* object = *cursor++;
        object->Reset();
        object->Reset();
    }
    return 0;
}
#pragma code_seg()
