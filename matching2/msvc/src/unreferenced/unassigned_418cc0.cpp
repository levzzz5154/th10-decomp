// 0x00418CC0: clear bit 0, latch it and reload the retail defaults
// The object pointer arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00418cc0 {
    unsigned char pad_000[0x14];
    int field_014;   // +0x14
    int field_018;   // +0x18
    int field_01C;   // +0x1C
    int field_020;   // +0x20
    unsigned int field_024;  // +0x24
    unsigned char pad_028[0x34 - 0x28];
    int field_034;   // +0x34
};

__declspec(noinline) void Reset3(ObjectAccessor_00418cc0* object);
#pragma code_seg(".text$01accessor")
void Reset3(ObjectAccessor_00418cc0* object) {
    unsigned int value = object->field_024 & ~1u;
    object->field_024 = value;
    if ((value & 1u) == 0) {
        value |= 1u;
        object->field_018 = 0;
        object->field_014 = 0xFFF0BDC1;
        object->field_01C = 0;
        object->field_020 = 0x476F78;
        object->field_024 = value;
    }
    object->field_018 = 0;
    object->field_01C = 0;
    object->field_014 = 0xFFFFFFFF;
    object->field_034 = 1;
}
#pragma code_seg()
