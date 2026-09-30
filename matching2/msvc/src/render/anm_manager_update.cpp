// Animation manager update passes (0x00448860, 0x00448900), their scheduler
// callbacks (0x004485D0, 0x004485E0), and VM removal (0x00448BB0).
//
// Each pass runs every VM on its list, removes the ones marked for removal or
// whose script finished, and threads the survivors into draw-order lists.
// Native LTCG passes the manager in EAX to the passes and in EDI (with the VM
// in ESI) to RemoveVm.
#include <stdlib.h>
#include "th10/game/entity.hpp"
#include "th10/render/anm_manager_lists.hpp"

extern "C" int __stdcall AnmVm_Run_0043ee30(AnmManagerVm* vm);

#pragma code_seg(".text$01a_primarytask")
extern "C" int __fastcall AnmManager_UpdatePrimaryTask_004485d0(AnmManager* manager) {
    return manager->UpdatePrimary();
}

#pragma code_seg(".text$01c_secondarytask")
extern "C" int __fastcall AnmManager_UpdateSecondaryTask_004485e0(AnmManager* manager) {
    return manager->UpdateSecondary();
}

#pragma code_seg(".text$01e_primary")
int AnmManager::UpdatePrimary() {
    AnmManagerVm* layer_tails[kAnmLayerCount + 1];
    for (int layer = 0; layer < kAnmLayerCount; ++layer) {
        layer_tails[layer] = &primary_layers[layer];
        layer_tails[layer]->next_in_layer = 0;
    }
    for (AnmVmNode* node = primary_head; node != 0;) {
        AnmManagerVm* vm = node->vm;
        AnmVmNode* next = node->next;
        if (vm->flags & kAnmVmMarkedForRemoval) {
            RemoveVm(vm);
        } else {
            if (vm->on_tick)
                vm->on_tick(vm);
            if (AnmVm_Run_0043ee30(vm)) {
                RemoveVm(vm);
            } else {
                layer_tails[vm->layer]->next_in_layer = vm;
                layer_tails[vm->layer] = vm;
                vm->next_in_layer = 0;
            }
        }
        ++updated_count;
        node = next;
    }
    return 1;
}

#pragma code_seg(".text$01g_secondary")
int AnmManager::UpdateSecondary() {
    secondary_layer.next_in_layer = 0;
    AnmManagerVm* tail = &secondary_layer;
    updated_count = 0;
    for (AnmVmNode* node = secondary_head; node != 0;) {
        AnmManagerVm* vm = node->vm;
        AnmVmNode* next = node->next;
        if (vm->flags & kAnmVmMarkedForRemoval) {
            RemoveVm(vm);
        } else {
            if (vm->on_tick)
                vm->on_tick(vm);
            if (AnmVm_Run_0043ee30(vm)) {
                RemoveVm(vm);
            } else {
                tail->next_in_layer = vm;
                tail = vm;
                vm->next_in_layer = 0;
            }
        }
        ++updated_count;
        node = next;
    }
    return 1;
}

#pragma code_seg(".text$01i_remove")
int AnmManager::RemoveVm(AnmManagerVm* vm) {
    AnmVmNode* node = &vm->manager_node;
    if (node == primary_tail)
        primary_tail = vm->manager_node.previous;
    if (node == primary_head)
        primary_head = vm->manager_node.next;
    if (node == secondary_tail)
        secondary_tail = vm->manager_node.previous;
    if (node == secondary_head)
        secondary_head = vm->manager_node.next;
    node->Unlink();
    vm->child_node.Unlink();

    if (vm >= &pool[0] && vm < &pool[kAnmVmPoolSize]) {
        pool_in_use[vm - pool] = 0;
        if (vm->heap_data)
            free(vm->heap_data);
        vm->heap_data = 0;
        Entity_Init(0, reinterpret_cast<Entity*>(vm));
        return 0;
    }
    if (vm) {
        if (vm->heap_data)
            free(vm->heap_data);
        vm->heap_data = 0;
        operator delete(vm);
    }
    return 0;
}
#pragma code_seg()
