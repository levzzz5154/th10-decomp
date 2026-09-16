// 0x421d90: mark one byte of the replay-work block and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_byte_mark_00421d90.json).

struct replaybytemark_00421d90 {
    unsigned char pad_00000[0x3ADA6E];
    unsigned char field_3ADA6E; // +0x3ada6e
    __declspec(noinline) void Mark();
};
typedef char replaybytemark_00421d90_size_must_fit[sizeof(replaybytemark_00421d90) == 0x3ADA6F ? 1 : -1];

#pragma code_seg(".text$01mark00421d90")
void replaybytemark_00421d90::Mark() {
    field_3ADA6E = 255;
}
#pragma code_seg()
