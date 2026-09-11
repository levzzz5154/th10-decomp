// 0x00409E20: retire both scheduler callbacks owned by a pair record.
// Each callback task carries status bits in the dword at +0x04; setting bit 1
// marks it for the scheduler teardown, which is how the pair installed by
// 0x004055C0 is released. Retail receives the pair in EAX and ends in a plain RET.

// Scheduler callback node; only the status dword at +0x04 is touched here.
struct SchedulerCallback {
    int priority;                       // +0x00
    unsigned int flags_04;              // +0x04, bit 1 retires the callback
    char unknown_08[0x18];
};

struct CallbackPair {
    char unknown_00[8];
    SchedulerCallback* primary_task;    // +0x08
    SchedulerCallback* secondary_task;  // +0x0C

    __declspec(noinline) void RetireCallbacks();
};

#pragma code_seg(".text$01f409e20")
void CallbackPair::RetireCallbacks() {
    if (this->primary_task)
        this->primary_task->flags_04 |= 2;
    if (this->secondary_task)
        this->secondary_task->flags_04 |= 2;
}
#pragma code_seg()
