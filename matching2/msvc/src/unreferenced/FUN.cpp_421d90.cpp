// 0x421d90: mark one byte of the replay-work block and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_byte_mark2.json).

struct replaybytemark2 {
    unsigned char pad_00000[0x3ADA6E];
    unsigned char field_3ADA6E; // +0x3ada6e
    __declspec(noinline) void Mark();
};
typedef char replaybytemark_00421d90_size_must_fit[sizeof(replaybytemark2) == 0x3ADA6F ? 1 : -1];

#pragma code_seg(".text$01mark00421d90")
void replaybytemark2::Mark() {
    field_3ADA6E = 255;
}
#pragma code_seg()
