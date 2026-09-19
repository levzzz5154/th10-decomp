// 0x00405450: arm a timer leaf whose record arrives in EAX and whose count comes
// on the stack; the count is stored as an int pair and as a float.
struct TimerArm_00405450 {
    int field_000;                       // +0x000
    int field_004;                       // +0x004
    float field_008;                     // +0x008
    int field_00c;                       // +0x00C
    unsigned int flags_010;              // +0x010
    __declspec(noinline) void Arm(int value);
};
#pragma code_seg(".text$01arm")
void TimerArm_00405450::Arm(int value) {
    if (!(flags_010 & 1u)) {
        field_004 = 0;
        field_000 = 0xFFF0BDC1;
        field_008 = 0.0f;
        field_00c = 0x00476F78;
        flags_010 |= 1u;
    }
    field_004 = value;
    field_000 = value - 1;
    field_008 = (float)value;
}
#pragma code_seg()
