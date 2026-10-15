// 0x00401510 - scheduler callback that prints the ASCII manager's main string
// queue: the task's context arrives in ECX and is handed on the stack to the
// draw at 0x00401760.
struct AsciiManager;
int __stdcall AsciiManager_DrawStrings(AsciiManager* thread);

int __fastcall AsciiManager_OnDraw(AsciiManager* thread) {
    return AsciiManager_DrawStrings(thread);
}
