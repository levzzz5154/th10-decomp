#include "th10/game/item_manager_destructor.hpp"
#pragma code_seg(".text$00element_ctor")
Item::Item() {
    InitializeAnimation();
}
#pragma code_seg(".text$01element_dtor")
Item::~Item() {
    if (resource)
        crt_free(resource);
    resource = 0;
}
#pragma code_seg()
