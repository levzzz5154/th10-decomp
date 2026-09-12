// 0x0044BEA0 - Move a menu cursor by delta, wrapping (or clamping) at the
// item-count boundary, then bypass any position listed in the skip table by
// advancing again with the same delta. Menu handlers call this on the
// up/down input edges; the pause menu also re-checks the moved result.
#include "th10/game/menu.hpp"

int MenuCursor_Advance(MenuCursor* cursor, int delta) {
    if (cursor->itemCount <= 0)
        return cursor->value;
    while (true) {
        int next = cursor->value + delta;
        cursor->value = next;
        while (next >= cursor->itemCount) {
            if (cursor->wrap != 0)
                next = cursor->value - cursor->itemCount;
            else
                next = cursor->itemCount - 1;
            cursor->value = next;
        }
        while (cursor->value < 0) {
            if (cursor->wrap != 0)
                cursor->value += cursor->itemCount;
            else
                cursor->value = 0;
        }
        int index = 0;
        while (true) {
            if (index >= cursor->skipCount)
                return cursor->value;
            if (cursor->skipValues[index] == cursor->value)
                break;
            ++index;
        }
    }
}
