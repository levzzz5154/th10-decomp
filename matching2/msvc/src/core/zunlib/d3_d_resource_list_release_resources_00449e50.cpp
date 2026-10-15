// Release each queued scheduler resource under the shared scheduler lock.
// Native LTCG supplies the receiver in EAX and the owner on the stack (RET 4).
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/game/resource_list_00449e50.hpp"

#pragma code_seg(".text$01release")
void ResourceList_00449e50::Release(ResourceListOwner_00449e50 owner) {
    TaskLink* node = first;
    if (node) {
        void (__stdcall *enter)(CriticalSection*) = EnterCriticalSection;
        void (__stdcall *leave)(CriticalSection*) = LeaveCriticalSection;
        do {
            SchedulerTask* resource = node->task;
            // Save the successor before removal can change the current link.
            TaskLink* next = node->next;
            if (resource) {
                enter(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                FuncCtrl_RemoveTask(resource, owner.scheduler);
                leave(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
            }
            node = next;
        } while (node);
    }
}
#pragma code_seg()
