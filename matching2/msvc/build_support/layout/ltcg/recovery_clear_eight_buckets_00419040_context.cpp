// Compiler context only; never selected as recovered game code.
#include "../../../src/game/hint/recovery_clear_eight_buckets.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryClearEightBucketsCompilerContext(
        Manager3** managers, int count) {
    while (count--)
        (*managers++)->ClearBuckets();
    return 0;
}
#pragma code_seg()
