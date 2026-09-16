// 0x421da0: mark one byte of the replay-work block and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_byte_mark_00421da0.json).

struct replaybytemark_00421da0 {
    unsigned char pad_00000[0x3ADA6C];
    unsigned char field_3ADA6C; // +0x3ada6c
    __declspec(noinline) void Mark();
};
typedef char replaybytemark_00421da0_size_must_fit[sizeof(replaybytemark_00421da0) == 0x3ADA6D ? 1 : -1];

#pragma code_seg(".text$01mark00421da0")
void replaybytemark_00421da0::Mark() {
    field_3ADA6C = 255;
}
#pragma code_seg()
