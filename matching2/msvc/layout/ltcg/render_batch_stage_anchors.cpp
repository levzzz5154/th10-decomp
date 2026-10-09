// Body compiled here only so this link derives its entry convention for
// the stage background task; the recovered function lives in
// src/game/player_set_scheduler_value_00405410.cpp.
struct PlayerSchedulerRecord {
    int field_00;
    int field_04;
    float field_08;
    int field_0C;
    int flags_10;
    __declspec(noinline) void SetSchedulerValue(int value);
};
#pragma code_seg(".text$000zt_timerset")
void PlayerSchedulerRecord::SetSchedulerValue(int value) {
    if (!(this->flags_10 & 1)) {
        this->field_04 = 0;
        this->field_00 = 0xFFF0BDC1;
        this->field_08 = 0.0f;
        this->field_0C = 0x476F78;
        this->flags_10 |= 1;
    }
    this->field_04 = value;
    this->field_00 = value - 1;
    this->field_08 = (float)value;
}
#pragma code_seg()
