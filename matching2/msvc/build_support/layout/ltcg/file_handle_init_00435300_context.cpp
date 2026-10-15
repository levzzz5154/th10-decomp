// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00435300_00435300.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall FileHandleInitContext_00435300(
    FileHandle_00435300** objects, int count) {
    while (count--) {
        FileHandle_Initialize_00435300(*objects++);
    }
    return 0;
}
#pragma code_seg()
