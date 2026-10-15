// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/timer_arm_record_00404ca0.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall TimerArmCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        ((TimerArmRecord_00404ca0*)items[index])->Arm();
    for (int index = 0; index < count; ++index)
        ((TimerArmRecord_0043c930*)items[index])->Arm();
    return 0;
}
#pragma code_seg()
