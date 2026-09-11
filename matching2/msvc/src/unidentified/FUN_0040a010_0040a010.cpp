// 0x0040A010: retire both scheduler callbacks of a pair and run the owner
// teardown. Unlike 0x00409E20 the two callback pointers are dereferenced without
// a null test, and the pair is then handed to the teardown at 0x00426F70.
// Retail receives the pair in EAX and tail-calls the teardown.

struct SchedulerCallback {
    int priority;                       // +0x00
    unsigned int flags_04;              // +0x04, bit 1 retires the callback
    char unknown_08[0x18];
};

struct CallbackPair {
    char unknown_00[8];
    SchedulerCallback* primary_task;    // +0x08
    SchedulerCallback* secondary_task;  // +0x0C

    __declspec(noinline) void DetachPairAndFinalize();
};

extern "C" __declspec(noinline) void RetireCallbackOwner_00426f70(CallbackPair* pair);

#pragma code_seg(".text$01f40a010")
void CallbackPair::DetachPairAndFinalize() {
    this->primary_task->flags_04 |= 2;
    this->secondary_task->flags_04 |= 2;
    RetireCallbackOwner_00426f70(this);
}
#pragma code_seg()
