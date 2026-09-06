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

struct RunOwner {
    int calls;
    int first_result;
    int later_result;
    int seven_calls;
    SchedulerCallback* deactivate;
};

static int ScriptedCallback(void* pointer) {
    assert(DAT_0049231c == 0);
    RunOwner* owner = static_cast<RunOwner*>(pointer);
    ++owner->calls;
    if (owner->deactivate != nullptr)
        owner->deactivate->flags &= ~2u;
    return owner->calls == 1 ? owner->first_result : owner->later_result;
}

static int SeventhCallback(void* pointer) {
    assert(DAT_0049231c == 1);
    ++static_cast<RunOwner*>(pointer)->seven_calls;
    return 1;
}

// Instruction-derived expectations: primary 0x449C30 resets the count;
// 0x449CB5/0x449CCB and secondary 0x449DE3 load the cached successor;
// the secondary switch at 0x449DBA only dispatches codes through five.
static void TestWalkerContracts(bool primary) {
    for (int scenario = 0; scenario < 10; ++scenario) {
        unsigned char device[0x90] = {};
        SchedulerCallback a = {}, b = {};
        RunOwner oa = {0, 1, 1, 0, nullptr};
        RunOwner ob = {0, 1, 1, 0, nullptr};
        a.function = b.function = ScriptedCallback;
        a.onResultSeven = b.onResultSeven = SeventhCallback;
        a.flags = b.flags = 2;
        a.owner = &oa;
        b.owner = &ob;
        a.node.owner = &a;
        b.node.owner = &b;
        auto register_callback = primary ? Scheduler_RegisterPrimary :
                                          Scheduler_RegisterSecondary;
        auto run = primary ? Scheduler_RunPrimary : Scheduler_RunSecondary;
        register_callback(&a, 0, device);
        register_callback(&b, 1, device);
        if (scenario == 1) b.function = nullptr; // null tail
        if (scenario == 2) a.function = nullptr; // null before live successor
        if (scenario == 3) ob.first_result = ob.later_result = 0; // retire tail
        if (scenario == 4) ob.first_result = 6;
        if (scenario == 5) ob.first_result = 7;
        if (scenario == 6) ob.first_result = 2;
        if (scenario == 7) { ob.first_result = 2; ob.deactivate = &b; }
        if (scenario == 8) ob.first_result = 4;
        if (scenario == 9) b.flags = 0;
        const int result = run(device);
        assert(result == (scenario == 8 ? 0 :
                          (scenario == 1 || scenario == 2) ? 1 : 2));
        assert(oa.calls == (scenario == 2 ? 0 :
                            scenario == 4 && primary ? 2 : 1));
        assert(ob.calls == ((scenario == 1 || scenario == 9) ? 0 :
                            (scenario == 6 || (scenario == 4 && primary)) ? 2 : 1));
        assert(ob.seven_calls == (scenario == 5 && primary ? 1 : 0));
        assert(DAT_0049231c == 0);
        if (scenario == 3) {
            assert(b.function == nullptr && b.owner == &ob);
            assert(b.node.next == nullptr && b.node.previous == nullptr);
            Scheduler_Remove(&b, device); // already unlinked: preserve state
            assert(b.owner == &ob && b.flags == 2);
        }
    }

    unsigned char device[0x90] = {};
    SchedulerCallback retained = {};
    retained.function = ScriptedCallback;
    retained.owner = &retained;
    SchedulerNode* head = ListHead(device, primary ? 0x14 : 0x38);
    head->owner = &retained;
    // 0x449F93/0x449F95 protects a matching sentinel (no predecessor).
    Scheduler_Remove(&retained, device);
    assert(retained.function == ScriptedCallback && retained.owner == &retained);
    assert(head->owner == &retained);
}

int main() {
    TestWalkerContracts(true);
    TestWalkerContracts(false);
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
