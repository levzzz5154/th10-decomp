// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0040ae50.cpp"

struct CachedSlot_00421d50 {
    unsigned char unknown_0000[0x3ADA74];
    void *cached;

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$05context")
extern "C" int __stdcall SmallPrivateAbiAContext(
        BulletManagerState_0040ae50 **states, int state_count,
        CachedSlot_00421d50 **slots, int slot_count) {
    while (state_count--) {
        states[0]->Initialize();
        ++states;
    }
    while (slot_count--) {
        slots[0]->Release();
        ++slots;
    }
    return 0;
}
#pragma code_seg()
