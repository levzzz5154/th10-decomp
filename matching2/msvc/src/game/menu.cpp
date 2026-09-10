#include "th10/game/menu_cursor.hpp"

#pragma code_seg(".text$01setwrap")
void MenuCursor::SetWrap(int enabled) {
    wrap = enabled;
}
#pragma code_seg(".text$03previous")
int MenuCursor::Previous() {
    return Advance(-1);
}
#pragma code_seg(".text$05next")
int MenuCursor::Next() {
    return Advance(1);
}
#pragma code_seg(".text$07setcount")
void MenuCursor::SetItemCount(int count) {
    item_count = count;
}
#pragma code_seg(".text$09getselection")
int MenuCursor::GetSelection() const {
    return selection;
}
#pragma code_seg(".text$11reset")
void MenuCursor::Reset() {
    history_depth = 0;
    selection = 0;
    disabled_count = 0;
    wrap = 1;
    item_count = 999;
}
#pragma code_seg(".text$13clear")
void MenuCursor::ClearDisabledItems() {
    disabled_count = 0;
}
#pragma code_seg(".text$15disable")
void MenuCursor::DisableItem(int item) {
    disabled_items[disabled_count] = item;
    ++disabled_count;
}
#pragma code_seg()

#pragma code_seg(".text$17push")
void MenuCursor::PushSelection() {
    selection_history[history_depth] = selection;
    item_count_history[history_depth] = item_count;
    ++history_depth;
    if (history_depth >= 16)
        history_depth = 15;
    disabled_count = 0;
}

#pragma code_seg(".text$19pop")
void MenuCursor::PopSelection() {
    --history_depth;
    if (history_depth < 0)
        history_depth = 0;
    selection = selection_history[history_depth];
    item_count = item_count_history[history_depth];
    disabled_count = 0;
}

#pragma code_seg(".text$21advance")
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
