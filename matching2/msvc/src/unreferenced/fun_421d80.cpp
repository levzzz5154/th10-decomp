// 0x421d80: mark one byte of the replay-work block and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_byte_mark.json).

struct replaybytemark {
    unsigned char pad_00000[0x3ADA6A];
    unsigned char field_3ADA6A; // +0x3ada6a
    __declspec(noinline) void Mark();
};
typedef char replaybytemark_00421d80_size_must_fit[sizeof(replaybytemark) == 0x3ADA6B ? 1 : -1];

#pragma code_seg(".text$01mark00421d80")
void replaybytemark::Mark() {
    field_3ADA6A = 255;
}
#pragma code_seg()
