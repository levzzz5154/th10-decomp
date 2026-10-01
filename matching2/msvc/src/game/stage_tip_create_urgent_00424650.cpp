// 0x00424650: create a tip that hurries the ones already showing.
//
// Every tip in the current list has its countdown stepped once, then the new
// tip is created with a shorter stay, a red tint and a second less to show.
//
// Native LTCG passes the manager in ESI.
#include "th10/game/stage_tip_create.hpp"

#pragma code_seg(".text$03urgent")
__declspec(noinline) StageTip* __stdcall StageTip_CreateUrgent_00424650(
        StageTipManager* manager, const char* text, const StageTipPosition* position) {
    StageTipNode* next;
    for (StageTipNode* node = manager->lists[8 + GameState()->list].next; node; node = next) {
        next = node->next;
        StageTip* shown = node->owner;
        if (shown->selection > 0)
            shown->selection--;
    }
    StageTip* tip = StageTip_Create_0041a120(manager, text, position);
    int value = tip->display_value -= 60;
    if (value <= 0)
        tip->display_value = 1;
    tip->duration = 90;
    tip->state = 0xFFFF8080;
    tip->selection = 30;
    return tip;
}
#pragma code_seg()
