#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"

// 0x00406770..0x00406797: the bullet manager's update task (registered by
// 0x00405E20 at priority 0x14); runs the bullet update 0x004065C0.
// The flag gate is the first half of the same thiscall function whose tail
// enters RecoverySlotTable::Rearm with the object in ESI.
struct RecoverySlotOwner {
    unsigned char pad_00[0x58];
    unsigned int field_58;
};

struct RecoverySlotTable {
    unsigned char pad_0000[0x14];
    void* heads[6];
    void* tails[6];
    unsigned char pad_0044[0x5C - 0x44];
    int active;
    unsigned char slots[2000 * 0x7F0];

    __declspec(noinline) int Rearm();
    __declspec(noinline) int OnUpdate();
};

#pragma code_seg(".text$05canrearm")
__declspec(noinline) int RecoverySlotTable::OnUpdate() {
    RecoverySlotOwner* owner =
        *reinterpret_cast<RecoverySlotOwner**>(&g_game);
    if (owner != 0 && ((owner->field_58 >> 2 | owner->field_58) & 1) != 0)
        return 1;
    return Rearm();
}
#pragma code_seg()
