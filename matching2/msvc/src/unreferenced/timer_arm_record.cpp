// Two timer-arm leaves of one record family, each entered with its record in
// EAX (a convention no C++ declaration names).  0x00404CA0 arms the record at
// +0x70 and 0x0043C930 the identical layout at +0x30: while the flag word is
// not yet running, the four fields take the stopped sentinels, then the three
// live fields are forced to the -1/0/0 stopped state.  The leading store of the
// second arm is spelled through a pointer so the scheduler keeps it ahead of the
// flag load, which retail does and a direct member store does not.
struct TimerArmRecord {
    unsigned char pad_000[0x70];
    int field_070;
    int field_074;
    int field_078;
    int field_07c;
    unsigned int flags_080;
    __declspec(noinline) void Arm();
};

struct TimerArmRecord2 {
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
void TimerArmRecord::Arm() {
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
void TimerArmRecord2::Arm() {
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
