// Compiler context only; never selected as recovered game code.
#include "../../src/game/player_hud_update_00408d60.cpp"

typedef int (__fastcall *HudCallback_00408d60)(PlayerHud_00408d60* hud);

// The scheduler holds the callback by address and runs it on its context.
#pragma code_seg(".text$a95context")
int __stdcall PlayerHudUpdateContext(HudCallback_00408d60* slot, PlayerHud_00408d60* hud,
        GameSelection_00408d60** selection, ScoreFile_00408d60*** scores) {
    *selection = &g_selection;
    *scores = &data_0047783c;
    *slot = PlayerManagerPrimary_00409220;
    return (*slot)(hud);
}
#pragma code_seg()
