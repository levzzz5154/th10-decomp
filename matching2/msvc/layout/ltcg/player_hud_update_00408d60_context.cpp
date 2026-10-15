// Compiler context only; never selected as recovered game code.
#include "../../src/game/card/card_update.cpp"

typedef int (__fastcall *HudCallback_00408d60)(Card_00408d60* hud);

// The scheduler holds the callback by address and runs it on its context.
#pragma code_seg(".text$a95context")
int __stdcall CardUpdateContext(HudCallback_00408d60* slot, Card_00408d60* hud,
        GameSelection_00408d60** selection, ScoreFile_00408d60*** scores) {
    *selection = &g_selection;
    *scores = &data_0047783c;
    *slot = CardPrimary_00409220;
    return (*slot)(hud);
}
#pragma code_seg()
