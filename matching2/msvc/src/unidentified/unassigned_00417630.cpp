// 0x00417630: return the address of the field block at +0x2FC
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00417630 {
    unsigned char pad_000[0x2FC];
};

__declspec(noinline) char* Offset_00417630(ObjectAccessor_00417630* object);
#pragma code_seg(".text$01accessor")
char* Offset_00417630(ObjectAccessor_00417630* object) {
    return (char*)object + 0x2FC;
}
#pragma code_seg()
