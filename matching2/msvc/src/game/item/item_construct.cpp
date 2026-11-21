// 0x0041ACF0: Item_Construct
#include "th10/game/item_record.hpp"

// 0x0041ACF0: initialize one element of the item manager's pool.
Item* __fastcall Item_Construct(Item* item) {
    item->InitializeAnimation();
    return item;
}
