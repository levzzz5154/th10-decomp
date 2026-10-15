// The ASCII manager's update task, main-queue draw task and info-vtable size.
#include "th10/game/ascii_manager.hpp"

// 0x004014F0: the ASCII manager's update task. It empties both string queues
// (the frame's code fills them again before the draw tasks run), counts the
// update and reports success.

int AsciiManager::OnUpdate() {
    record_count = 0;
    late_record_count = 0;
    ++update_count;
    return 1;
}

// 0x00401510 - scheduler callback that prints the ASCII manager's main string
// queue: the task's context arrives in ECX and is handed on the stack to the
// draw at 0x00401760.
struct AsciiManager;
int __stdcall AsciiManager_DrawStrings(AsciiManager* thread);

int __fastcall AsciiManager_OnDraw(AsciiManager* thread) {
    return AsciiManager_DrawStrings(thread);
}

// 0x00401C90: the only slot of the ASCII manager's info vtable (0x0046CB14,
// "AsciiInf"): the manager's allocation size, 0x89AC bytes.
extern "C" int __cdecl AsciiManager_GetSize() {
    return 0x89AC;
}
