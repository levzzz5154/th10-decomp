// Compiler-only models of the two callees whose private conventions the game
// state destructor depends on.
#include "th10/core/func_ctrl.hpp"
#include "th10/game/enemy_manager_dependencies.hpp"

void __cdecl operator delete(void*);
extern "C" SprtCtrl* g_sprt_ctrl;
extern "C" void __cdecl crt_free(void* memory);

#pragma code_seg(".text$07release")
void AnimationResource6::Release() {
    if (resource_108 == 0)
        return;
    g_sprt_ctrl->MarkResourceForRemoval(this);
    for (int index = 0; index < entry_count_10c; ++index) {
        AnimationResourceEntry* entry = &entries_120[index];
        if (entry->handle != 0) {
            entry->handle->slot2();
            entry->handle = 0;
        }
        if (entry->allocation != 0) {
            crt_free(entry->allocation);
            entry->allocation = 0;
        }
    }
    if (entries_120 != 0) {
        crt_free(entries_120);
        entries_120 = 0;
    }
    if (auxiliary_118 != 0) {
        crt_free(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (auxiliary_11c != 0) {
        crt_free(auxiliary_11c);
        auxiliary_11c = 0;
    }
    if (auxiliary_12c != 0) {
        crt_free(auxiliary_12c);
        auxiliary_12c = 0;
    }
    if (resource_108 != 0) {
        crt_free(resource_108);
        resource_108 = 0;
    }
}
#pragma code_seg()

#pragma code_seg(".text$13remove")
extern "C" __declspec(noinline) void __stdcall FuncCtrl_Remove(FuncCtrl* scheduler, SchedulerTask* task) {
    if (!task) return;
    TaskLink* node = &scheduler->primary.link;
    while (node) {
        if (node->task == task) break;
        node = node->next;
    }
    if (!node) {
        node = &scheduler->secondary.link;
        while (node) {
            if (node->task == task) break;
            node = node->next;
        }
    }
    if (node && node->previous) {
        node->Unlink();
        task->on_tick = 0;
        if (task->heap_owned) delete task;
    }
}
#pragma code_seg()
