// 0x00418EE0: Hint_Destroy
#include "th10/game/resource_cleanup.hpp"
#include "th10/render/animation_mark_for_removal.hpp"

// Remove the task pair, mark ten animation handles and their children for
// removal, save hints when requested, then release all owned bucket chains.
extern "C" unsigned char g_screen_mode;
extern "C" void* g_hint;
extern "C" const char str_hint_auto_path[];
extern "C" void __stdcall SaveHints(HintBucketsView* manager,const char* path);
#pragma code_seg(".text$01cleanup")
extern "C" __declspec(noinline) void __stdcall Hint_Destroy(HintBucketsView* manager) {
    RemoveScheduledTaskPair(&manager->tasks);
    AnimationBuckets* buckets=g_sprt_ctrl;
    int* key=manager->keys;
    int remaining=10;
    do {
        StopAnimation(buckets,*key);
        *key=0;
        ++key;
    } while (--remaining);
    if (g_screen_mode==2) SaveHints(manager,str_hint_auto_path);
    manager->ClearBuckets();
    g_hint=0;
}
#pragma code_seg()
