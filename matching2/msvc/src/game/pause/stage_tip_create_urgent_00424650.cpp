// 0x00424650: create a tip that hurries the ones already showing.
//
// Every tip in the current list has its countdown stepped once, then the new
// tip is created with a shorter stay, a red tint and a second less to show.
//
// Native LTCG passes the manager in ESI.
#include "th10/game/hint_data_create.hpp"

#pragma code_seg(".text$03urgent")
__declspec(noinline) HintData* __stdcall HintData_CreateUrgent_00424650(
        Hint* manager, const char* text, const HintDataPosition* position) {
    HintDataNode* next;
    for (HintDataNode* node = manager->lists[8 + GameState()->list].next; node; node = next) {
        next = node->next;
        HintData* shown = node->owner;
        if (shown->selection > 0)
            shown->selection--;
    }
    HintData* tip = HintData_Create_0041a120(manager, text, position);
    int value = tip->display_value -= 60;
    if (value <= 0)
        tip->display_value = 1;
    tip->duration = 90;
    tip->state = 0xFFFF8080;
    tip->selection = 30;
    return tip;
}
#pragma code_seg()
