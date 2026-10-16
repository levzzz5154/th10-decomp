// 0x00417650: return the address of the field block at +0x340
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00417650 {
    unsigned char pad_000[0x340];
};

__declspec(noinline) char* Offset4(ObjectAccessor_00417650* object);
#pragma code_seg(".text$01accessor")
char* Offset4(ObjectAccessor_00417650* object) {
    return (char*)object + 0x340;
}
#pragma code_seg()
