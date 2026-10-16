// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_402040.cpp"

#pragma code_seg(".text$03context")
int __stdcall FreeContext_00402040(void** blocks, int count) {
    for (int i = 0; i < count; ++i) {
        FreeBlock(blocks[i]);
    }
    return 0;
}
#pragma code_seg()
