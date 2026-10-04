// Compiler context only; never selected as recovered game code.
#include "../../src/game/player_hud_start_spell_00409280.cpp"

// The spell card setup hands the panel its record index, name and duration.
#pragma code_seg(".text$0044e100_context")
void __stdcall PlayerHudStartSpellContext(PlayerHud_00408d60** panels, const char** names,
        int count, GameSelection_00409280** selection) {
    *selection = &g_selection;
    for (int i = 0; i < count; ++i)
        panels[i]->StartSpell(i, names[i], count);
}
#pragma code_seg()
