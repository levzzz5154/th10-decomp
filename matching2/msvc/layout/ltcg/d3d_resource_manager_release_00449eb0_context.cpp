// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "th10/platform/thread_sync.hpp"
#include "../../src/core/zunlib/platform_stop_worker_0044c150.cpp"
#include "../../src/core/zunlib/d3_d_resource_manager_release_00449eb0.cpp"

// Stand-in for 0x00449E50 (src/core/zunlib/d3_d_resource_list_release_resources_00449e50.cpp)
// with the parameter order this caller's evaluation order requires. It keeps
// the list in EAX and the owner on the stack.
#pragma code_seg(".text$07release")
__declspec(noinline) void __stdcall ReleaseResourceList_00449eb0(
        Scheduler* owner, ResourceList_DestroyABI_00449e50* list) {
    TaskLink* node = list->first;
    if (node) {
        void (__stdcall *enter)(CriticalSection*) = EnterCriticalSection;
        void (__stdcall *leave)(CriticalSection*) = LeaveCriticalSection;
        do {
            SchedulerTask* resource = node->task;
            TaskLink* next = node->next;
            if (resource) {
                enter(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                Scheduler_RemoveTask(resource, *static_cast<Scheduler* volatile*>(&owner));
                leave(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
            }
            node = next;
        } while (node);
    }
}
#pragma code_seg()

#pragma code_seg(".text$30context")
extern "C" void __stdcall D3DResourceManagerReleaseContext_00449eb0(
        D3DResourceManager_00449eb0** managers, int count) {
    while (count--)
        (*managers++)->ReleaseResources();
}
#pragma code_seg()
