// 0x004189F0: increment the counters at +0x48 and +0x4C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004189f0 {
    unsigned char pad_000[0x48];
    int field_048;
    int field_04C;
    __declspec(noinline) void IncrementCounters();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004189f0::IncrementCounters() {
    ++field_048;
    ++field_04C;
}
#pragma code_seg()
