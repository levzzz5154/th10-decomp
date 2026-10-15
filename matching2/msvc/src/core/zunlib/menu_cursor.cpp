#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_3.hpp"
#include "th10/source_views/menu_9d8ff0_4.hpp"
#include "th10/source_views/menu_9d8ff0_5.hpp"
#include "th10/source_views/menu_9d8ff0_6.hpp"
#include "th10/source_views/menu_9d8ff0_7.hpp"
#include "th10/source_views/menu_9d8ff0_8.hpp"
void MenuCursor::PushSelection() {
    selection_history[history_depth] = selection;
    item_count_history[history_depth] = item_count;
    ++history_depth;
    if (history_depth >= 16)
        history_depth = 15;
    disabled_count = 0;
}


#include "../../../include/th10/source_views/menu_9d8ff0_9.hpp"
#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_3.hpp"
#include "th10/source_views/menu_9d8ff0_4.hpp"
#include "th10/source_views/menu_9d8ff0_5.hpp"
#include "th10/source_views/menu_9d8ff0_6.hpp"
#include "th10/source_views/menu_9d8ff0_7.hpp"
#include "th10/source_views/menu_9d8ff0_8.hpp"
#include "th10/source_views/menu_9d8ff0_9.hpp"
void MenuCursor::PopSelection() {
    --history_depth;
    if (history_depth < 0)
        history_depth = 0;
    selection = selection_history[history_depth];
    item_count = item_count_history[history_depth];
    disabled_count = 0;
}


#include "../../../include/th10/source_views/menu_9d8ff0_10.hpp"
#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_3.hpp"
#include "th10/source_views/menu_9d8ff0_4.hpp"
#include "th10/source_views/menu_9d8ff0_5.hpp"
#include "th10/source_views/menu_9d8ff0_6.hpp"
#include "th10/source_views/menu_9d8ff0_7.hpp"
#include "th10/source_views/menu_9d8ff0_8.hpp"
#include "th10/source_views/menu_9d8ff0_9.hpp"
#include "th10/source_views/menu_9d8ff0_10.hpp"
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

