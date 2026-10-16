#include "../../../src/unreferenced/timer_arm_float.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall TimerArmFloatCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        ((TimerArm*)items[index])->Arm(index + 1);
    return 0;
}
#pragma code_seg()
