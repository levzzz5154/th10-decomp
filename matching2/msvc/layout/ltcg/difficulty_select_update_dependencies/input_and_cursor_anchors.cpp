// Real bodies of the key test 0x0040ACE0, the bounded counter store
// 0x0040AD20 and the cursor history push 0x0044BE20 the difficulty selection
// screen 0x00430320 calls, unselected here. The key test is left free to inline, as it is in the
// screens' own translation unit.
#define noinline
#define code_seg(name) code_seg(".text$0040ace0_fn")
#include "../../../src/game/eclview/input_mask_active_0040ace0.cpp"
#undef code_seg
#undef noinline
#include "th10/game/menu_cursor.hpp"
#pragma code_seg(".text$0044be20_fn")
void MenuCursor::PushSelection() {
    selection_history[history_depth] = selection;
    item_count_history[history_depth] = item_count;
    ++history_depth;
    if (history_depth >= 16)
        history_depth = 15;
    disabled_count = 0;
}
#pragma code_seg(".text$0040ad20_fn")
__declspec(noinline) unsigned int __fastcall UpdateBoundedCounter(
        unsigned int requested, unsigned int* counter) {
    unsigned int value = counter[2];
    if (value) {
        if ((int)requested >= (int)value)
            --value;
        else
            value = (((int)requested < 0) - 1) & requested;
    } else {
        value = requested;
    }
    *counter = value;
    return value;
}
#pragma code_seg()
