struct TimerArmRecord_00404ca0 {
    unsigned char pad_000[0x70];
    int field_070;
    int field_074;
    int field_078;
    int field_07c;
    unsigned int flags_080;
    __declspec(noinline) void Arm();
};

struct TimerArmRecord_0043c930 {
    unsigned char pad_000[0x2C];
    int field_02c;
    int field_030;
    int field_034;
    int field_038;
    int field_03c;
    unsigned int flags_040;
    __declspec(noinline) void Arm();
};

#pragma code_seg(".text$01arm")
void TimerArmRecord_00404ca0::Arm() {
    if (!(flags_080 & 1u)) {
        field_074 = 0;
        field_070 = 0xFFF0BDC1;
        field_078 = 0;
        field_07c = 0x00476F78;
        flags_080 |= 1u;
    }
    field_074 = 0;
    field_078 = 0;
    field_070 = -1;
}
#pragma code_seg()

#pragma code_seg(".text$03arm2")
void TimerArmRecord_0043c930::Arm() {
    volatile int* p = &field_02c; *p = 1;
    if (!(flags_040 & 1u)) {
        field_034 = 0;
        field_030 = 0xFFF0BDC1;
        field_038 = 0;
        field_03c = 0x00476F78;
        flags_040 |= 1u;
    }
    field_034 = 0;
    field_038 = 0;
    field_030 = -1;
}
#pragma code_seg()
