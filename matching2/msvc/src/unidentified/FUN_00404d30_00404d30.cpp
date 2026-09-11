// 0x00404D30: clear the trajectory step counter of a state record.
// The counter at +0x84 is the integer 0x00404D10 converts to a float and passes
// to the trajectory evaluator at 0x0044C350. Retail receives the record in EAX
// and ends in a plain RET.

struct TrajectoryState {
    char unknown_00[0x84];
    int step_84;                        // +0x84

    __declspec(noinline) void ResetStep();
};

#pragma code_seg(".text$01f404d30")
void TrajectoryState::ResetStep() {
    this->step_84 = 0;
}
#pragma code_seg()
