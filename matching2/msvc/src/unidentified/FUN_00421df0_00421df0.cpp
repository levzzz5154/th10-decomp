// 0x421df0: clear one replay-work field and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_slot_clear_b_00421df0.json).

struct ReplaySlotClearB_00421df0 {
    unsigned char pad_00000[0x3ADA70];
    int field_3ADA70; // +0x3ada70
    __declspec(noinline) void Clear();
};
typedef char ReplaySlotClearB_00421df0_size_must_fit[sizeof(ReplaySlotClearB_00421df0) == 0x3ADA74 ? 1 : -1];

#pragma code_seg(".text$01clear00421df0")
void ReplaySlotClearB_00421df0::Clear() {
    field_3ADA70 = 0;
}
#pragma code_seg()
