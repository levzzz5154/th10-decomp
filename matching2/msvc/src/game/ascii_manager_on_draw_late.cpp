// 0x00401520 - scheduler callback that prints the game thread's late text
// queue. The task's context arrives in ECX and is handed to the draw at
// 0x00401A50, whose whole-program convention takes it in EBX.
#include "th10/game/ascii_manager.hpp"

#pragma code_seg(".text$000lb1task")
int __fastcall AsciiManager_OnDrawLate(AsciiManager* thread) {
    return thread->DrawLateRecords();
}
#pragma code_seg()
