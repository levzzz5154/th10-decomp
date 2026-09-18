// Compiler context only; never selected as recovered game code.
#include "../../src/game/recovery_clear_eight_buckets_00419040.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryClearEightBucketsCompilerContext(
        Manager_00419040** managers, int count) {
    while (count--)
        (*managers++)->ClearBuckets();
    return 0;
}
#pragma code_seg()
