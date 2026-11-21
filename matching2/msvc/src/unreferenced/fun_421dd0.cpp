// 0x421dd0: mark one byte of the replay-work block and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_byte_mark6.json).

struct replaybytemark6 {
    unsigned char pad_00000[0x3ADA69];
    unsigned char field_3ADA69; // +0x3ada69
    __declspec(noinline) void Mark();
};
typedef char replaybytemark_00421dd0_size_must_fit[sizeof(replaybytemark6) == 0x3ADA6A ? 1 : -1];

#pragma code_seg(".text$01mark00421dd0")
void replaybytemark6::Mark() {
    field_3ADA69 = 255;
}
#pragma code_seg()
