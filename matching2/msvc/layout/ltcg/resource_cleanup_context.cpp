// Unselected compiler context; includes the genuine maintained helper bodies.
#define TH10_CLEAR_BUCKETS_CODE_SEG ".text$03buckets"
#include "../../src/game/hint/recovery_clear_eight_buckets_00419040.cpp"
#undef TH10_CLEAR_BUCKETS_CODE_SEG
#include "../../src/game/hint/resource_manager_cleanup_00418ee0.cpp"
#define TH10_SCHEDULER_REMOVE_ONLY
#define TH10_SCHEDULER_REMOVE_CODE_SEG ".text$05remove"
#include "../../src/core/zunlib/scheduler_tasks.cpp"
#undef TH10_SCHEDULER_REMOVE_CODE_SEG
#undef TH10_SCHEDULER_REMOVE_ONLY

#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) void __stdcall ResourceCleanupContext(
        Manager_00419040** managers, int count) {
    while (count--) ResourceCleanup(*managers++);
}
#pragma code_seg()
