// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_44c770.cpp"

struct JoystickSlot2 {
    __declspec(noinline) int Configure(int device, int flags, int property_owner);
};

#pragma code_seg(".text$05context")
int __stdcall JoystickSlotsCompilerContext(
        JoystickSlot** release_slots,
        JoystickSlot2** setup_slots,
        int count, int device, int flags, int property_owner) {
    for (int index = 0; index < count; ++index) {
        release_slots[index]->Release();
        setup_slots[index]->Configure(device, flags, property_owner);
    }
    return 0;
}
#pragma code_seg()
