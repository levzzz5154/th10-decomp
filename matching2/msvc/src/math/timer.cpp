// 0x0042C620..0x0042C66F: set the title-state timer target.
//
// Retail enters this member with the state in EAX and the target in ECX.  The
// task-local native-LTCG layout supplies that internal convention; the body
// remains ordinary, readable C++.
extern "C" float data_00476f78;

struct GameStateTimer_0042c620 {
    unsigned char unknown_00[0x20];
    int timer_target;
    unsigned char unknown_24[0x28C];
    int timer_previous;
    int timer_current;
    int timer_elapsed;
    float* timer_speed;
    unsigned int timer_flags;

    __declspec(noinline) void SetTimerTarget(int target);
};

typedef char GameStateTimer_0042c620_size_must_fit[
    sizeof(GameStateTimer_0042c620) == 0x2C4 ? 1 : -1];

#pragma code_seg(".text$01settarget")
void GameStateTimer_0042c620::SetTimerTarget(int target) {
    timer_target = target;
    if ((timer_flags & 1) == 0) {
        timer_current = 0;
        timer_previous = 0xFFF0BDC1;
        timer_elapsed = 0;
        timer_speed = &data_00476f78;
        timer_flags |= 1;
    }
    timer_current = 0;
    timer_elapsed = 0;
    timer_previous = -1;
}
#pragma code_seg()
