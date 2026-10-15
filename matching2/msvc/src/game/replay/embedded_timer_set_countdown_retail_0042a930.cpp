// 0x0042A930..0x0042A96A: lazily initialise an embedded frame countdown
// timer, then store its integer and floating-point countdown values.
//
// The retail caller supplies the timer object in EAX and the frame count on
// the stack. Native MSVC LTCG recovers that internal register convention when
// this method is compiled with its task-specific compiler context.
extern "C" float g_game_speed;

struct EmbeddedTimerState_0042a930 {
    unsigned char unknown_00[0x14];
    int target_14;
    int current_18;
    float previous_1c;
    float* speed_20;
    unsigned int flags_24;

    __declspec(noinline) void SetCountdown(int frames);
};

#pragma code_seg(".text$01setcountdown")
void EmbeddedTimerState_0042a930::SetCountdown(int frames) {
    if ((this->flags_24 & 1) == 0) {
        this->current_18 = 0;
        this->target_14 = 0xFFF0BDC1;
        this->previous_1c = 0.0f;
        this->speed_20 = &g_game_speed;
        this->flags_24 |= 1;
    }
    this->current_18 = frames;
    this->target_14 = frames - 1;
    this->previous_1c = (float)frames;
}
#pragma code_seg()
