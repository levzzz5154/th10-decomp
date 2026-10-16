#include <stdlib.h>
#include "th10/render/anm_manager_lists.hpp"
void __stdcall Entity_Init(Entity*);
#pragma code_seg(".text$10removevm")
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
        Entity_Init(reinterpret_cast<Entity*>(vm));
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
