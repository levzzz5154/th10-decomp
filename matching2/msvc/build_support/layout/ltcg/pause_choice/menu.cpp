#include "th10/game/pause_choice/cursor.hpp"
#pragma code_seg(".text$90push")
void PauseChoiceCursor::PushSelection() {
    selection_history[history_depth] = selection;
    item_count_history[history_depth] = item_count;
    ++history_depth;
    if (history_depth >= 16)
        history_depth = 15;
    disabled_count = 0;
}

#pragma code_seg(".text$92pop")
void PauseChoiceCursor::PopSelection() {
    --history_depth;
    if (history_depth < 0)
        history_depth = 0;
    selection = selection_history[history_depth];
    item_count = item_count_history[history_depth];
    disabled_count = 0;
}

#pragma code_seg(".text$94advance")
int PauseChoiceCursor::Advance(int delta) {
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
