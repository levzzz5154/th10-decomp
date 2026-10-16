// 0x0041F820: clear 0x20 and set 0x10 at +0x35C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_0041f820 {
    unsigned char pad_000[0x35C];
    unsigned int field_35C;
    __declspec(noinline) void UpdateFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0041f820::UpdateFlag() {
    field_35C = (field_35C & ~0x20u) | 0x10u;
}
#pragma code_seg()
