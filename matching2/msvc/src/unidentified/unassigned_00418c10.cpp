// 0x00418C10: clear the counters at +0x48 and +0x4C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418c10 {
    unsigned char pad_000[0x48];
    int field_048;
    int field_04C;
    __declspec(noinline) void ClearCounters();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418c10::ClearCounters() {
    field_048 = 0;
    field_04C = 0;
}
#pragma code_seg()
