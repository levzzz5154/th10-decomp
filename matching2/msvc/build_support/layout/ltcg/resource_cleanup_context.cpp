// Unselected compiler context; includes the genuine maintained helper bodies.
#define TH10_CLEAR_BUCKETS_CODE_SEG ".text$03buckets"
#include "../../../src/game/hint/hint_clear_buckets.cpp"
#undef TH10_CLEAR_BUCKETS_CODE_SEG
#include "../../../src/game/hint/hint_destroy.cpp"
#define TH10_SCHEDULER_REMOVE_ONLY
#define TH10_SCHEDULER_REMOVE_CODE_SEG ".text$05remove"
#include "../../../src/core/zunlib/scheduler_tasks.cpp"
#undef TH10_SCHEDULER_REMOVE_CODE_SEG
#undef TH10_SCHEDULER_REMOVE_ONLY

#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) void __stdcall ResourceCleanupContext(
        HintBucketsView** managers, int count) {
    while (count--) Hint_Destroy(*managers++);
}
#pragma code_seg()
