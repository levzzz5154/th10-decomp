#include "full_script_context.cpp"
#include "main_menu_no_global.cpp"
// Complete maintained 0x44BE20 body from src/game/menu.cpp.
#pragma code_seg(".text$0044be20_fn")
void MenuCursor::PushSelection() {
    selection_history[history_depth] = selection;
    item_count_history[history_depth] = item_count;
    ++history_depth;
    if (history_depth >= 16)
        history_depth = 15;
    disabled_count = 0;
}
#pragma code_seg()
