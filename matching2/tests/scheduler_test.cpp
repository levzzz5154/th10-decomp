#include "th10/game/scheduler.hpp"

#include <cassert>
#include <cstdlib>
#include <cstring>

unsigned int DAT_00492274;
unsigned char DAT_0049231c;

extern "C" void* operator_new(unsigned int size) {
    return std::malloc(size);
}
extern "C" void _free(void* memory) {
    std::free(memory);
}

extern "C" void EnterCriticalSection(void*) {}
extern "C" void LeaveCriticalSection(void*) {}

static int replacementCalls;
static int dummyIndex;
static int removedAnimation;
static int dispatchedIndex;
static int dispatchedHandle;
static void DispatchAnimation(int index, void*, int handle) {
    dispatchedIndex = index;
    dispatchedHandle = handle;
}
static void RemoveAnimation(void*, int handle) { removedAnimation = handle; }
static int DummyConfigure(void*, const char* name, int index, int flags) {
    assert((std::strcmp(name, "dummy") == 0 ||
            std::strcmp(name, "UnPause") == 0) && flags == 0);
    dummyIndex = index;
    return 0;
}

static int Replacement(void*) {
    ++replacementCalls;
    return 37;
}

static int Callback(void*) {
    return 1;
}

static int RemoveOnRun(void*) {
    return 0;
}

static int StopWithOne(void*) {
    return 3;
}

static int StopWithNegativeOne(void*) {
    return 5;
}

static SchedulerNode* ListHead(unsigned char* device, unsigned int offset) {
    return (SchedulerNode*)(device + offset);
}

int main() {
    assert(GameState_DispatchDummy((void*)1, 0, DummyConfigure) == 0);
    assert(dummyIndex == 3);
    assert(GameState_DispatchDummy((void*)1, 0x10, DummyConfigure) == 0);
    assert(dummyIndex == 4);
    int objectValue = 0;
    int maximumValue = 12;
    GameState_UpdateFrameMaximum(7, &objectValue, &maximumValue);
    assert(objectValue == 7 && maximumValue == 12);
    GameState_UpdateFrameMaximum(19, &objectValue, &maximumValue);
    assert(objectValue == 19 && maximumValue == 19);
    unsigned int stateFlags = 0x31;
    int animationHandle = 44;
    int currentFrame = 2;
    removedAnimation = 0;
    GameState_Unpause(&stateFlags, (void*)1, &animationHandle, 17,
                      &currentFrame, DummyConfigure, RemoveAnimation);
    assert(stateFlags == 0x21 && dummyIndex == 7);
    assert(removedAnimation == 44 && animationHandle == 0 && currentFrame == 17);
    unsigned char animationState[0x300] = {};
    *(int*)(animationState + 0x2C4 + 3 * 4) = 91;
    GameState_DispatchAnimationSlot(animationState, 3, (void*)1,
                                    DispatchAnimation);
    assert(dispatchedIndex == 3 && dispatchedHandle == 91);
    GameState_DispatchAnimationSlotSecondary(animationState, 3, (void*)1,
                                             DispatchAnimation);
    assert(dispatchedIndex == 3 && dispatchedHandle == 91);
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

    unsigned char secondaryDevice[0x50];
    std::memset(secondaryDevice, 0, sizeof(secondaryDevice));
    SchedulerCallback* owned = Scheduler_CreateAndRegisterSecondary(
        Callback, (void*)0xCAFE, secondaryDevice);
    assert(owned != 0);
    assert(owned->owner == (void*)0xCAFE);
    assert((owned->flags & 2u) != 0);
    SchedulerNode* secondaryHead = ListHead(secondaryDevice, 0x38);
    assert(secondaryHead->next == &owned->node);
    assert(owned->node.previous == secondaryHead);
    Scheduler_Remove(owned, secondaryDevice);
    assert(secondaryHead->next == 0);

    unsigned char dispatchDevice[0x50];
    std::memset(dispatchDevice, 0, sizeof(dispatchDevice));
    SchedulerCallback* retire = SchedulerCallback_Create(RemoveOnRun);
    assert(retire != 0);
    retire->flags |= 2u;
    Scheduler_RegisterSecondary(retire, 0, dispatchDevice);
    SchedulerCallback* keep = SchedulerCallback_Create(Callback);
    assert(keep != 0);
    keep->flags |= 2u;
    Scheduler_RegisterSecondary(keep, 1, dispatchDevice);
    assert(Scheduler_RunSecondary(dispatchDevice) == 2);
    assert(ListHead(dispatchDevice, 0x38)->next == &keep->node);
    Scheduler_Remove(keep, dispatchDevice);

    unsigned char terminalDevice[0x50];
    std::memset(terminalDevice, 0, sizeof(terminalDevice));
    SchedulerCallback* one = SchedulerCallback_Create(StopWithOne);
    one->flags |= 2u;
    Scheduler_RegisterSecondary(one, 0, terminalDevice);
    assert(Scheduler_RunSecondary(terminalDevice) == 1);
    Scheduler_Remove(one, terminalDevice);

    SchedulerCallback* negative = SchedulerCallback_Create(
        StopWithNegativeOne);
    negative->flags |= 2u;
    Scheduler_RegisterSecondary(negative, 0, terminalDevice);
    assert(Scheduler_RunSecondary(terminalDevice) == -1);
    Scheduler_Remove(negative, terminalDevice);

    std::free(first);
    std::free(second);
    std::free(third);
    std::free(secondary);
    return 0;
}
