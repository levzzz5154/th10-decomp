// 0x00413120: copy three words into the block at +0x0C
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Triple_00413120 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct ObjectAccessor_00413120 {
    unsigned char pad_000[0x0C];
    Triple_00413120 block;   // +0x0C
    __declspec(noinline) void Assign(const Triple_00413120& value);
};
#pragma code_seg(".text$01accessor")
void ObjectAccessor_00413120::Assign(const Triple_00413120& value) {
    block = value;
}
#pragma code_seg()
