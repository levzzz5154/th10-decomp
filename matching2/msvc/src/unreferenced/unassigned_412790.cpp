// 0x00412790: store a value into the indexed sixteen-byte record
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

__declspec(noinline) void SetRecord(unsigned int value, int index, void* base);
#pragma code_seg(".text$01accessor")
void SetRecord(unsigned int value, int index, void* base) {
    *(unsigned int*)((char*)base + (index + 0x24A) * 16) = value;
}
#pragma code_seg()
