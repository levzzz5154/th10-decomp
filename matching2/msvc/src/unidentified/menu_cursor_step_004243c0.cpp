// 0x004243C0 and 0x004243D0: move a menu cursor forwards or backwards by the
// step the caller passes in EAX; the cursor is the stack argument.  Both are
// compiled in the menu_cursor native-LTCG cluster so the call into
// MenuCursor::Advance keeps its private entry (cursor in EAX, delta on the stack).
#include "th10/game/menu_cursor.hpp"

#pragma code_seg(".text$12layoutb")
__declspec(noinline) int StepMenuCursor(int step, MenuCursor* cursor) {
    return cursor->Advance(step);
}
#pragma code_seg(".text$12layoutc")
__declspec(noinline) int StepMenuCursorBack(int step, MenuCursor* cursor) {
    return cursor->Advance(-step);
}
#pragma code_seg()
