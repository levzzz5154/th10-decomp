// 0x00401510 - scheduler callback that prints the game thread's main text
// queue: the task's context arrives in ECX and is handed on the stack to the
// draw at 0x00401760.
struct GameThreadText;
int __stdcall GameThreadText_DrawRecords_00401760(GameThreadText* thread);

int __fastcall FUN_00401510(GameThreadText* thread) {
    return GameThreadText_DrawRecords_00401760(thread);
}
