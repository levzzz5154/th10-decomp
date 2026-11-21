// 0x004088C0: SpellCard_CountByDifficulty
extern signed char g_spell_card_difficulties[110];

// 0x004088C0: count a signed pattern value across the fixed 22-by-5 table.
// Both retail call sites provide the query in EDX and leave ECX unrelated, so
// the unused first fastcall argument records the compiler-facing ABI.
int __fastcall SpellCard_CountByDifficulty(void*, int query) {
    int matches = 0;
    for (int index = 0; index < 110; ++index) {
        if (g_spell_card_difficulties[index] == query)
            ++matches;
    }
    return matches;
}
