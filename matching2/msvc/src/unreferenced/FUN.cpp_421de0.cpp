// 0x421de0: clear one replay-work field and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_slot_clear_a.json).

struct ReplaySlotClearA {
    unsigned char pad_00000[0x3ADA64];
    int field_3ADA64; // +0x3ada64
    __declspec(noinline) void Clear();
};
typedef char ReplaySlotClearA_00421de0_size_must_fit[sizeof(ReplaySlotClearA) == 0x3ADA68 ? 1 : -1];

#pragma code_seg(".text$01clear00421de0")
void ReplaySlotClearA::Clear() {
    field_3ADA64 = 0;
}
#pragma code_seg()
