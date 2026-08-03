#include "th10/game/linked_pool_append.hpp"

#ifdef _MSC_VER
extern "C" void* sub_452493(unsigned long);
#endif

#include <cstring>

// 0x0042AA50 - Allocate and append one pool payload. Retail carries the
// pool index in ESI (compiler-reserved register, like the release path
// at 0x0042AB20) and takes the manager as the stack argument. After
// zeroing the 0x18A1-word payload the retail body wires the self
// pointer at word 0x1518, points the entry cursor at word 0x1519, and
// initializes the three-word intrusive node; it then follows the
// sentinel chain at manager word offset pool_index*3 + 0xF to the last
// node and appends. The dead "patch a non-null successor" branch after
// the tail walk (its condition is false by construction) is dropped.
#ifdef _MSC_VER
__declspec(naked) LinkedPoolPayload* LinkedPool_AllocateAndAppendRetail() {
    __asm {
        push 6284h
        call sub_452493
        mov edx, eax
        add esp, 4
        test edx, edx
        jz loc_42AA9E
        push edi
        xor eax, eax
        mov ecx, 18A1h
        mov edi, edx
        rep stosd
        mov [edx+5460h], edx
        lea eax, [edx+5464h]
        mov [edx+6274h], eax
        mov [edx+6278h], edx
        mov dword ptr [edx+627Ch], 0
        mov dword ptr [edx+6280h], 0
        pop edi
        jmp loc_42AAA0
loc_42AA9E:
        xor edx, edx
loc_42AAA0:
        lea eax, [edx+6278h]
        mov edx, [esp+4]
        lea ecx, [esi+esi*2+0Fh]
        lea ecx, [edx+ecx*4]
        mov edx, [ecx+4]
        test edx, edx
        jz loc_42AAC2
loc_42AAB8:
        mov ecx, [ecx+4]
        mov edx, [ecx+4]
        test edx, edx
        jnz loc_42AAB8
loc_42AAC2:
        mov edx, [ecx+4]
        test edx, edx
        jz loc_42AAD2
        mov [eax+4], edx
        mov edx, [ecx+4]
        mov [edx+8], eax
loc_42AAD2:
        mov [ecx+4], eax
        mov [eax+8], ecx
        ret 4
    }
}
#endif

LinkedPoolPayload* LinkedPool_AllocateAndAppend(LinkedPoolManager* manager,
                                                uint32_t pool_index,
                                                void* (*allocate)(uint32_t)) {
    LinkedPoolPayload* payload =
        allocate != 0 ? (LinkedPoolPayload*)allocate(0x6284) : 0;
    if (payload == 0) {
        return 0;
    }
    memset(payload, 0, sizeof(*payload));
    payload->self = payload;
    payload->entry_cursor = payload->reserved;
    payload->node.owner = payload;
    payload->node.next = 0;
    payload->node.previous = 0;

    LinkedPoolNode* tail = &manager->lists[pool_index];
    while (tail->next != 0) {
        tail = tail->next;
    }
    tail->next = &payload->node;
    payload->node.previous = tail;
    return payload;
}
