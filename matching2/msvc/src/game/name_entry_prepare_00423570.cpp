// 0x00423570..0x004236E9: enter the finished game's score and set up the
// name entry of the result screen.
//
// A cleared extra stage is recorded as stage 8, so the stage and the stage
// table row are switched around the insertion. A score that does not reach
// the table only sets `no_entry`. Otherwise the new row is selected, the
// character grid is reset, and the name starts as the one entered last time;
// unless that is blank the grid cursor steps back once. The name length is
// the name without its trailing spaces.
#include "th10/game/name_entry_prepare_00423570.hpp"
#include <string.h>

// Select an item, keeping the selection inside a non-empty list.
static inline void SelectItem_00423570(MenuCursor* cursor, int item) {
    if (cursor->item_count != 0)
        cursor->selection = item >= cursor->item_count ? cursor->item_count - 1 : item;
    else
        cursor->selection = item;
}

#pragma code_seg(".text$00423570_fn")
void __stdcall PrepareNameEntry_00423570(NameEntryMenu_00423570* menu) {
    if (data_00474c44.stage == 7 && menu->extra_cleared != 0) {
        data_00477848 = &data_00474788[8];
        data_00474c44.stage = 8;
        data_00474c44.stage_shown = 8;
    }
    int rank = data_0047783c->players[data_00474c44.shot_type + data_00474c44.character * 3]
                   .table.InsertScore();
    if (data_00474c44.stage == 7 && menu->extra_cleared != 0) {
        data_00477848 = &data_00474788[7];
        data_00474c44.stage = 7;
        data_00474c44.stage_shown = 7;
    }
    if (rank >= 0) {
        menu->rows.item_count = 25;
        menu->rows.wrap = 1;
        SelectItem_00423570(&menu->rows, rank);
        SelectItem_00423570(&menu->alphabet, 0);
        menu->alphabet.item_count = (int)strlen(data_004746d8);
        menu->alphabet.wrap = 1;
        strcpy(menu->name, data_0047783c->last_name);
        menu->name_length = 0;
        if (strcmp(menu->name, "        ") != 0)
            menu->alphabet.Advance(-1);
        int length;
        for (length = 8; length > 0; --length) {
            if (menu->name[length - 1] != ' ')
                break;
        }
        menu->name_length = length;
        menu->no_entry = 0;
    } else {
        menu->no_entry = 1;
    }
}
#pragma code_seg()
