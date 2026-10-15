// 0x004369E0..0x00436A10: reset the ownership words of the record.
struct Object_004369e0 {
    unsigned char pad_000[0x100];
    unsigned int field_100;          // +0x100
    unsigned int field_104;          // +0x104
    unsigned int field_108;          // +0x108
    unsigned char pad_10c[8];        // +0x10C (two reserved words)
    unsigned int field_114;          // +0x114
    unsigned int field_118;          // +0x118
    unsigned int field_11c;          // +0x11C
    unsigned int field_120;          // +0x120
    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01accessor")
void Object_004369e0::Reset() {
    field_100 = 0xffffffff;
    field_104 = 0;
    field_108 = 0;
    field_114 = 0;
    field_11c = 0;
    field_118 = 0;
    field_120 = 0;
}
#pragma code_seg()
