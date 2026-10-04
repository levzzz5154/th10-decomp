// 0x00401520 - scheduler callback that prints the game thread's late text
// queue. The task's context arrives in ECX and is handed to the draw at
// 0x00401A50, whose whole-program convention takes it in EBX.
#include "th10/game/game_thread_text.hpp"

#pragma code_seg(".text$000lb1task")
int __fastcall GameThreadText_DrawLateTask_00401520(GameThreadText* thread) {
    return thread->DrawLateRecords();
}
#pragma code_seg()
