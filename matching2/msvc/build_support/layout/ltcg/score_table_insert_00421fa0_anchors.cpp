// Compiler context only: the body of 0x0044BEA0 (recovered in
// build_support/layout/units/menu_9d8ff0.cpp), so the pass derives its cursor-in-EAX convention. These
// bytes are not selected.
#include "th10/game/menu_cursor.hpp"

#pragma code_seg(".text$0044bea0_fn")
int MenuCursor::Advance(int delta) {
    int count = item_count;
    if (count > 0) {
    retry_selection:
        selection += delta;
        while (selection >= item_count) {
            if (wrap)
                selection -= count;
            else
                selection = count - 1;
        }
        while (selection < 0) {
            if (wrap)
                selection += count;
            else
                selection = 0;
        }
        for (int index = 0; index < disabled_count; ++index) {
            if (disabled_items[index] == selection)
                goto retry_selection;
        }
    }
    return selection;
}
#pragma code_seg()
