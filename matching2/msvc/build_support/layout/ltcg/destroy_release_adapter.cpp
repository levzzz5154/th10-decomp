#include "th10/platform/thread_sync.hpp"
#include "th10/game/resource_list_destroy_abi.hpp"
#pragma code_seg(".text$07release")
void ResourceList_DestroyABI_00449e50::Release(FuncCtrl* owner) {
    TaskLink* node = first;
    if (node) {
        void (__stdcall *enter)(CriticalSection*) = EnterCriticalSection;
        void (__stdcall *leave)(CriticalSection*) = LeaveCriticalSection;
        do {
            SchedulerTask* resource = node->task;
            TaskLink* next = node->next;
            if (resource) {
                enter(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                FuncCtrl_RemoveTask(resource, *static_cast<FuncCtrl* volatile*>(&owner));
                leave(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
            }
            node = next;
        } while (node);
    }
}
#pragma code_seg()
