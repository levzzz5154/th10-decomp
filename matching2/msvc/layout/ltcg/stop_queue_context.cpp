// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0043ddb0.cpp"
#pragma code_seg(".text$03context")
int __stdcall StopQueueCompilerContext(StopQueue_0043ddb0** items, int count, int index) {
    while (count--) {
        (*items++)->QueueEffectStop(index);
    }
    return 0;
}
#pragma code_seg()
