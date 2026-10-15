#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_3.hpp"
#include "th10/source_views/menu_9d8ff0_4.hpp"
#include "th10/source_views/menu_9d8ff0_5.hpp"
#include "th10/source_views/menu_9d8ff0_6.hpp"
void MenuCursor::ClearDisabledItems() {
    disabled_count = 0;
}


#include "../../../include/th10/source_views/menu_9d8ff0_7.hpp"
#include "th10/source_views/menu_9d8ff0_0.hpp"
#include "th10/source_views/menu_9d8ff0_1.hpp"
#include "th10/source_views/menu_9d8ff0_2.hpp"
#include "th10/source_views/menu_9d8ff0_3.hpp"
#include "th10/source_views/menu_9d8ff0_4.hpp"
#include "th10/source_views/menu_9d8ff0_5.hpp"
#include "th10/source_views/menu_9d8ff0_6.hpp"
#include "th10/source_views/menu_9d8ff0_7.hpp"
void MenuCursor::DisableItem(int item) {
    disabled_items[disabled_count] = item;
    ++disabled_count;
}

