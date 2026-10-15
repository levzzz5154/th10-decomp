// 0x00408C90: create the spell-card manager (Card, card.cpp). A manager that fails to initialize is destroyed
// again and the factory returns null; the compiler-generated cleanup at
// 0x00465860 frees the block if the constructor throws.
#include "th10/game/card_create.hpp"

#pragma code_seg(".text$04create")
Card_00408c90* __stdcall Card_Create_00408c90() {
    Card_00408c90* manager = new Card_00408c90;
    if (manager->Initialize()) {
        delete manager;
        return 0;
    }
    return manager;
}
#pragma code_seg()
