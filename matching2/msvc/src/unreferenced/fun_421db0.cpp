// 0x421db0: mark one byte of the replay-work block and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_byte_mark4.json).

struct replaybytemark4 {
    unsigned char pad_00000[0x3ADA6B];
    unsigned char field_3ADA6B; // +0x3ada6b
    __declspec(noinline) void Mark();
};
typedef char replaybytemark_00421db0_size_must_fit[sizeof(replaybytemark4) == 0x3ADA6C ? 1 : -1];

#pragma code_seg(".text$01mark00421db0")
void replaybytemark4::Mark() {
    field_3ADA6B = 255;
}
#pragma code_seg()
