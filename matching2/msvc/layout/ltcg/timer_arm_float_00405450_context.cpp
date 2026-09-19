#include "../../src/unidentified/timer_arm_float_00405450.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall TimerArmFloatCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        ((TimerArm_00405450*)items[index])->Arm(index + 1);
    return 0;
}
#pragma code_seg()
