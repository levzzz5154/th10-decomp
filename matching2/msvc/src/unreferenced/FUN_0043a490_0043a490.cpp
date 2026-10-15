// 0x43a490: write the pair of defaults and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (sound_pair_clear_0043a490.json).

struct SoundPairClear_0043a490 {
    int field_000; // +0x0
    int field_004; // +0x4
    __declspec(noinline) void Clear();
};
typedef char SoundPairClear_0043a490_size_must_fit[sizeof(SoundPairClear_0043a490) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01clear0043a490")
void SoundPairClear_0043a490::Clear() {
    field_000 = 0;
    field_004 = 0;
}
#pragma code_seg()
