// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0044c620_0044c620.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResetCompilerContext(CameraPairReset_0044c620** objects, int count) {
    CameraPairReset_0044c620** cursor = objects;
    while (count--) {
        CameraPairReset_0044c620* object = *cursor++;
        object->Reset();
        object->Reset();
    }
    return 0;
}
#pragma code_seg()
