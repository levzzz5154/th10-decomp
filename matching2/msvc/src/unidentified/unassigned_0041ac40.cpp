// 0x0041AC40: latch bit 0 and reload the retail defaults
// The object pointer arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0041ac40 {
    unsigned char pad_000[0x20];
    int field_020;   // +0x20
    int field_024;   // +0x24
    int field_028;   // +0x28
    int field_02C;   // +0x2C
    unsigned int field_030;  // +0x30
};

__declspec(noinline) void Reset_0041ac40(ObjectAccessor_0041ac40* object);
#pragma code_seg(".text$01accessor")
void Reset_0041ac40(ObjectAccessor_0041ac40* object) {
    if ((object->field_030 & 1u) == 0) {
        object->field_024 = 0;
        object->field_020 = 0xFFF0BDC1;
        object->field_028 = 0;
        object->field_02C = 0x476F78;
        object->field_030 |= 1u;
    }
    object->field_024 = 0;
    object->field_028 = 0;
    object->field_020 = 0xFFFFFFFF;
}
#pragma code_seg()
