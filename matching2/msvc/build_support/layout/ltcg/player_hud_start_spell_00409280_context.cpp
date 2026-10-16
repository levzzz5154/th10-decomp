// Compiler context only; never selected as recovered game code.
#include "../../../src/game/card/card_start_spell.cpp"

// The spell card setup hands the panel its record index, name and duration.
#pragma code_seg(".text$0044e100_context")
void __stdcall CardStartSpellContext(Card4** panels, const char** names,
        int count, GameSelection2** selection) {
    *selection = &g_selection;
    for (int i = 0; i < count; ++i)
        panels[i]->StartSpell(i, names[i], count);
}
#pragma code_seg()
