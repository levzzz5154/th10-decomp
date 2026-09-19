// 0x004130C0: return the address of the field block at +0xC
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004130c0 {
    unsigned char pad_000[0xC];
};

__declspec(noinline) char* Offset_004130c0(ObjectAccessor_004130c0* object);
#pragma code_seg(".text$01accessor")
char* Offset_004130c0(ObjectAccessor_004130c0* object) {
    return (char*)object + 0xC;
}
#pragma code_seg()
