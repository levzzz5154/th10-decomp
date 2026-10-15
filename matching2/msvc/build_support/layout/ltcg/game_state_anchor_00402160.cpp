// Compiler-only models of the two callees whose private conventions the game
// state destructor depends on.
#include "th10/core/func_ctrl.hpp"
#include "th10/game/enemy_manager_dependencies_0040d530.hpp"

void __cdecl operator delete(void*);
extern "C" SprtCtrl* g_sprt_ctrl;
extern "C" void __cdecl entry_free_00452422(void* memory);

#pragma code_seg(".text$07release")
void AnimationResource_00447810::Release() {
    if (resource_108 == 0)
        return;
    g_sprt_ctrl->MarkResourceForRemoval(this);
    for (int index = 0; index < entry_count_10c; ++index) {
        AnimationResourceEntry_00447810* entry = &entries_120[index];
        if (entry->handle != 0) {
            entry->handle->slot2();
            entry->handle = 0;
        }
        if (entry->allocation != 0) {
            entry_free_00452422(entry->allocation);
            entry->allocation = 0;
        }
    }
    if (entries_120 != 0) {
        entry_free_00452422(entries_120);
        entries_120 = 0;
    }
    if (auxiliary_118 != 0) {
        entry_free_00452422(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (auxiliary_11c != 0) {
        entry_free_00452422(auxiliary_11c);
        auxiliary_11c = 0;
    }
    if (auxiliary_12c != 0) {
        entry_free_00452422(auxiliary_12c);
        auxiliary_12c = 0;
    }
    if (resource_108 != 0) {
        entry_free_00452422(resource_108);
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
