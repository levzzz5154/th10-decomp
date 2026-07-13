#include "th10/game/scheduler.hpp"

#include <cassert>
#include <cstdlib>
#include <cstring>

unsigned int DAT_00492274;
unsigned char DAT_0049231c;

extern "C" void* operator_new(unsigned int size) {
    return std::malloc(size);
}

extern "C" void EnterCriticalSection(void*) {}
extern "C" void LeaveCriticalSection(void*) {}

static int replacementCalls;

static int Replacement(void*) {
    ++replacementCalls;
    return 37;
}

static int Callback(void*) {
    return 1;
}

static SchedulerNode* ListHead(unsigned char* device, unsigned int offset) {
    return (SchedulerNode*)(device + offset);
}

int main() {
    unsigned char device[0x80];
    std::memset(device, 0, sizeof(device));

    SchedulerCallback* first = SchedulerCallback_Create(Callback);
    SchedulerCallback* second = SchedulerCallback_Create(Callback);
    SchedulerCallback* third = SchedulerCallback_Create(Callback);
    assert(first != 0 && second != 0 && third != 0);
    assert(first->function == Callback);
    assert(first->node.owner == first);
    assert((first->flags & 1) != 0);

    assert(Scheduler_RegisterPrimary(first, 30, device) == 0);
    assert(Scheduler_RegisterPrimary(second, 10, device) == 0);
    third->onReplace = Replacement;
    assert(Scheduler_RegisterPrimary(third, 20, device) == 37);
    assert(replacementCalls == 1);
    assert(third->onReplace == 0);

    SchedulerNode* head = ListHead(device, 0x14);
    assert(head->next == &second->node);
    assert(second->node.next == &third->node);
    assert(third->node.next == &first->node);
    assert(first->node.next == 0);
    assert(second->node.previous == head);
    assert(third->node.previous == &second->node);
    assert(first->node.previous == &third->node);

    SchedulerCallback* secondary = SchedulerCallback_Create(Callback);
    assert(Scheduler_RegisterSecondary(secondary, 4, device) == 0);
    assert(ListHead(device, 0x38)->next == &secondary->node);
    assert(DAT_0049231c == 0);

    std::free(first);
    std::free(second);
    std::free(third);
    std::free(secondary);
    return 0;
}
