// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00405730_00405730.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN00405730CompilerContext(void** pairs, int count) {
    void** cursor = pairs;
    while (count--) {
        void* pair = *cursor++;
        FUN_00405730_ReleasePair(pair);
        FUN_00405730_ReleasePair(pair);
    }
    return 0;
}
#pragma code_seg()
