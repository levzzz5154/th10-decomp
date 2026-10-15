#include "th10/source_views/menu_9d8ff0_0.hpp"
void MenuCursor::SetWrap(int enabled) {
    wrap = enabled;
}


#include "../../../include/th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
int MenuCursor::Previous() {
    return Advance(-1);
}


#include "../../../include/th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
int MenuCursor::Next() {
    return Advance(1);
}


#include "../../../include/th10/source_views/menu_9d8ff0_3.hpp"
#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_3.hpp"
void MenuCursor::SetItemCount(int count) {
    item_count = count;
}


#include "../../../include/th10/source_views/menu_9d8ff0_4.hpp"
#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_3.hpp"
#include "th10/source_views/menu_9d8ff0_4.hpp"
int MenuCursor::GetSelection() const {
    return selection;
}


#include "../../../include/th10/source_views/menu_9d8ff0_5.hpp"
#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_3.hpp"
#include "th10/source_views/menu_9d8ff0_4.hpp"
#include "th10/source_views/menu_9d8ff0_5.hpp"
void MenuCursor::Reset() {
    history_depth = 0;
    selection = 0;
    disabled_count = 0;
    wrap = 1;
    item_count = 999;
}

