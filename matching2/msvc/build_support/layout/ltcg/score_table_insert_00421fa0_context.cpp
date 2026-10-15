// Compiler context only; never selected as recovered game code.
#include "../../../src/game/mother/score_table_insert_00421fa0.cpp"
#include "th10/game/name_entry_prepare_00423570.hpp"

extern "C" int __cdecl ScoreTableInsertEscape(void* pointer, int value);

// A caller that keeps the table across calls (so it travels in EDI), lets
// the address of the game counters escape and reaches the name entry
// preparation.
#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall ScoreTableInsertContext(ScoreTable_00421fa0* tables, int count,
                                                 NameEntryMenu_00423570* menu) {
    int total = ScoreTableInsertEscape(&data_00474c44, 0);
    PrepareNameEntry_00423570(menu);
    for (int index = 0; index < count; ++index) {
        ScoreTable_00421fa0* table = &tables[index];
        total += table->InsertScore();
        total += time_00452b71(&table->records[0][0].time);
        table->records[0][0].score = total;
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()
