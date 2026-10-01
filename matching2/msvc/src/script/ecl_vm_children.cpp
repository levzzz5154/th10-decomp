// 0x0044FD10..0x0044FDA1: tick the embedded interpreter and heap children.
// A failed root stops the owner; finished children are unlinked and freed.
#include "th10/script/ecl_children.hpp"
#include <stdlib.h>
#pragma code_seg(".text$03tick")
extern "C" __declspec(noinline) int __stdcall EclVm_TickChildren(EclChildOwner* owner, float delta) {
    EclChildNode* node = &owner->children;
    int first = 1; // The embedded root is never freed as a heap child.
    while (node) {
        EclChildNode* next = node->next;
        owner->active = node->state;
        if (first) {
            if (EclVm_RunInterpreter(owner->active, delta)) return -1;
            first = 0;
        } else if (EclVm_RunInterpreter(owner->active, delta)) {
            free(owner->active);
            node->Unlink();
            free(node);
        }
        node = next;
    }
    owner->active = &owner->root;
    return 0;
}
#pragma code_seg()
