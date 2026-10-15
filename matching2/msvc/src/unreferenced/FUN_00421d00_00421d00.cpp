// 0x421d00: write the pair of defaults and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (replay_marker_clear.json).

struct ReplayMarkerClear {
    unsigned char pad_000[0x38C];
    int field_38C; // +0x38c
    int field_390; // +0x390
    __declspec(noinline) void Clear();
};
typedef char ReplayMarkerClear_00421d00_size_must_fit[sizeof(ReplayMarkerClear) == 0x394 ? 1 : -1];

#pragma code_seg(".text$01clear00421d00")
void ReplayMarkerClear::Clear() {
    field_38C = -2;
    field_390 = 0;
}
#pragma code_seg()
