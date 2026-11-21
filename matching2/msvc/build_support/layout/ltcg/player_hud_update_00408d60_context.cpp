// Compiler context only; never selected as recovered game code.
#include "../../../src/game/card/card_update.cpp"

typedef int (__fastcall *HudCallback_00408d60)(CardUpdateView* hud);

// The scheduler holds the callback by address and runs it on its context.
#pragma code_seg(".text$a95context")
int __stdcall CardUpdateContext(HudCallback_00408d60* slot, CardUpdateView* hud,
        GameSelection** selection, ScoreFile*** scores) {
    *selection = &g_selection;
    *scores = &g_score;
    *slot = CardPrimary;
    return (*slot)(hud);
}
#pragma code_seg()
