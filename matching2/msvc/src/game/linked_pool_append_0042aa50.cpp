// 0x0042AA50: allocate a page and append it to a slot's list.
//
// The new page's link goes after the last node of the list. The slot arrives
// in ESI and the owner on the stack; the link is returned in EAX.
#include "th10/game/linked_pool_append.hpp"

#pragma code_seg(".text$a05m_append")
PoolLink_0042aa50* PoolOwner_0042aa50::AppendPage(int slot) {
    PoolLink_0042aa50* link = &(new PoolPage_0042aa50)->link;
    PoolLink_0042aa50* tail = &lists[slot];
    while (tail->next)
        tail = tail->next;
    if (tail->next) {
        link->next = tail->next;
        tail->next->previous = link;
    }
    tail->next = link;
    link->previous = tail;
    return link;
}
#pragma code_seg()
