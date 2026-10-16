// Compiler context only; never selected as recovered game code.
#include "../../../src/game/mother/score_table_insert.cpp"
#include "th10/game/name_entry_prepare.hpp"

extern "C" int __cdecl ScoreTableInsertEscape(void* pointer, int value);

// A caller that keeps the table across calls (so it travels in EDI), lets
// the address of the game counters escape and reaches the name entry
// preparation.
#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall ScoreTableInsertContext(ScoreTable* tables, int count,
                                                 NameEntryMenu* menu) {
    int total = ScoreTableInsertEscape(&g_globals_score, 0);
    PrepareNameEntry(menu);
    for (int index = 0; index < count; ++index) {
        ScoreTable* table = &tables[index];
        total += table->InsertScore();
        total += time2(&table->records[0][0].time);
        table->records[0][0].score = total;
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()
