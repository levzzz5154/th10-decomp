extern "C" float g_game_speed;

struct PathState_00417800 {
    unsigned char unknown_00[0x40];
    int reset_value_40;
    int reset_value_44;
    int reset_value_48;
    float* default_time_scale_4c;
    unsigned int flags_50;
    unsigned char unknown_54[4];
    int reset_value_58;
    int reset_value_5c;

    __declspec(noinline) int Reset();
};

#pragma code_seg(".text$00417800_fn")
int PathState_00417800::Reset() {
    if ((this->flags_50 & 1) == 0) {
        this->reset_value_44 = 0;
        this->reset_value_40 = -999999;
        this->reset_value_48 = 0;
        this->default_time_scale_4c = &g_game_speed;
        this->flags_50 |= 1;
    }
    this->reset_value_44 = 0;
    this->reset_value_48 = 0;
    this->reset_value_40 = -1;
    this->reset_value_58 = 0;
    this->reset_value_5c = 0;
    return 0;
}
#pragma code_seg()
