#include "th10/game/resource_cleanup.hpp"
#include "th10/render/animation_mark_for_removal.hpp"

// Remove the task pair, mark ten animation handles and their children for
// removal, save hints when requested, then release all owned bucket chains.
extern "C" unsigned char data_00491d6a;
extern "C" void* g_hint;
extern "C" const char data_0046d6d8[];
extern "C" void __stdcall SaveHints(Manager_00419040* manager,const char* path);
#pragma code_seg(".text$01cleanup")
extern "C" __declspec(noinline) void __stdcall ResourceCleanup(Manager_00419040* manager) {
    RemoveScheduledTaskPair(&manager->tasks);
    AnimationBuckets* buckets=g_sprt_ctrl;
    int* key=manager->keys;
    int remaining=10;
    do {
        MarkAnimationForRemoval(buckets,*key);
        *key=0;
        ++key;
    } while (--remaining);
    if (data_00491d6a==2) SaveHints(manager,data_0046d6d8);
    manager->ClearBuckets();
    g_hint=0;
}
#pragma code_seg()
