// Compiler context only; never selected as recovered game code.
#include "../../src/render/anm_batch_flush.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnmBatchFlush00442F50CompilerContext(
    AnimationManager_00442F50** managers, int count) {
    int total = 0;
    while (count--) {
        total += (*managers++)->Flush();
    }
    return total;
}
#pragma code_seg()
