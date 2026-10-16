// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/timer_arm_record.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall TimerArmCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        ((TimerArmRecord*)items[index])->Arm();
    for (int index = 0; index < count; ++index)
        ((TimerArmRecord2*)items[index])->Arm();
    return 0;
}
#pragma code_seg()
