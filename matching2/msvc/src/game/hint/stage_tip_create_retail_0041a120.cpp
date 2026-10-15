// 0x0041A120: create a tip and append it to the current list.
//
// The tip starts with the default display settings, takes the caller's
// position and at most 64 characters of its text.
//
// Native LTCG leaves the manager and the text on the stack and passes the
// position in EBX.
#include <string.h>

#include "th10/game/stage_tip_create.hpp"

StageTip::StageTip() {
    memset(this, 0, sizeof(*this));
    node.Initialize(this);
    state = -1;
    duration = 300;
    scale = 1.0f;
    selection = -1;
}

#pragma code_seg(".text$01create")
__declspec(noinline) StageTip* __stdcall StageTip_Create_0041a120(
        StageTipManager* manager, const char* text, const StageTipPosition* position) {
    StageTip* tip = new StageTip;
    manager->lists[8 + GameState()->list].Append(&tip->node);
    tip->selection = 30;
    tip->position = *position;
    strncpy(tip->name, text, 0x40);
    tip->display_zero = 0;
    tip->display_mode = GameState()->display_mode;
    tip->display_value = GameState()->display_mode ? GameState()->display_value_alternate
                                                   : GameState()->display_value;
    return tip;
}
#pragma code_seg()
