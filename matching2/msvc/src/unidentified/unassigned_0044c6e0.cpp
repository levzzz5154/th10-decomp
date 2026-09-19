// 0x0044C6E0: copy a 64-byte value record into the object. The record arrives
// by value on the stack, which fixes the argument convention; the object itself
// arrives in EAX, which only the native /LTCG pass chooses, so this is a cluster.
struct UnassignedValues_0044c6e0 {
    unsigned int field_000;  // +0x0000
    unsigned int field_004;  // +0x0004
    unsigned int field_008;  // +0x0008
    unsigned int field_00c;  // +0x000C
    unsigned int field_010;  // +0x0010
    unsigned int field_014;  // +0x0014
    unsigned int field_018;  // +0x0018
    unsigned int field_01c;  // +0x001C
    unsigned int field_020;  // +0x0020
    unsigned int field_024;  // +0x0024
    unsigned int field_028;  // +0x0028
    unsigned int field_02c;  // +0x002C
    unsigned int field_030;  // +0x0030
    unsigned int field_034;  // +0x0034
    unsigned int field_038;  // +0x0038
    unsigned int field_03c;  // +0x003C
};

struct UnassignedSet_0044c6e0 {
    unsigned int field_000;  // +0x0000
    unsigned int field_004;  // +0x0004
    unsigned int field_008;  // +0x0008
    unsigned int field_00c;  // +0x000C
    unsigned int field_010;  // +0x0010
    unsigned int field_014;  // +0x0014
    unsigned int field_018;  // +0x0018
    unsigned int field_01c;  // +0x001C
    unsigned int field_020;  // +0x0020
    unsigned int field_024;  // +0x0024
    unsigned int field_028;  // +0x0028
    unsigned int field_02c;  // +0x002C
    unsigned int field_030;  // +0x0030
    unsigned int field_034;  // +0x0034
    unsigned int field_038;  // +0x0038
    unsigned int field_03c;  // +0x003C
    __declspec(noinline) void Set(UnassignedValues_0044c6e0 value);
};

#pragma code_seg(".text$01accessor")
void UnassignedSet_0044c6e0::Set(UnassignedValues_0044c6e0 value) {
    field_000 = value.field_000;
    field_004 = value.field_004;
    field_008 = value.field_008;
    field_00c = value.field_00c;
    field_010 = value.field_010;
    field_014 = value.field_014;
    field_018 = value.field_018;
    field_01c = value.field_01c;
    field_020 = value.field_020;
    field_024 = value.field_024;
    field_028 = value.field_028;
    field_02c = value.field_02c;
    field_030 = value.field_030;
    field_034 = value.field_034;
    field_038 = value.field_038;
    field_03c = value.field_03c;
}
#pragma code_seg()
