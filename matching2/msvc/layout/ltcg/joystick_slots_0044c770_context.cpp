// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0044c770.cpp"

struct JoystickSlot_0044c790 {
    __declspec(noinline) int Configure(int device, int flags, int property_owner);
};

#pragma code_seg(".text$05context")
int __stdcall JoystickSlotsCompilerContext(
        JoystickSlot_0044c770** release_slots,
        JoystickSlot_0044c790** setup_slots,
        int count, int device, int flags, int property_owner) {
    for (int index = 0; index < count; ++index) {
        release_slots[index]->Release();
        setup_slots[index]->Configure(device, flags, property_owner);
    }
    return 0;
}
#pragma code_seg()
