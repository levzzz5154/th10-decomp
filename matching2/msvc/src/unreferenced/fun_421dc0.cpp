// 0x421dc0: mark one byte of the replay-work block and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_byte_mark5.json).

struct replaybytemark5 {
    unsigned char pad_00000[0x3ADA68];
    unsigned char field_3ADA68; // +0x3ada68
    __declspec(noinline) void Mark();
};
typedef char replaybytemark_00421dc0_size_must_fit[sizeof(replaybytemark5) == 0x3ADA69 ? 1 : -1];

#pragma code_seg(".text$01mark00421dc0")
void replaybytemark5::Mark() {
    field_3ADA68 = 3;
}
#pragma code_seg()
