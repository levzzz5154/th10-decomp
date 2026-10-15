// 0x44c620: write the pair of defaults and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (camera_pair_reset.json).

struct CameraPairReset {
    int field_000; // +0x0
    int field_004; // +0x4
    __declspec(noinline) void Reset();
};
typedef char CameraPairReset_0044c620_size_must_fit[sizeof(CameraPairReset) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01reset0044c620")
void CameraPairReset::Reset() {
    field_004 = 0;
    field_000 = 0x3F800000;
}
#pragma code_seg()
