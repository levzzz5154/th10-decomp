// 0x00433570..0x00433B23: replay save screen of the title menu (and its
// five-entry phase table), shown after a game when the player chooses to
// keep the replay.
//
// Phase 0 opens the 25 numbered replays and runs phase 1 on the same frame.
// Phase 1 waits seven frames.  Phase 2 picks the slot; confirm stamps the
// recorded replay with the current time, proposes the name entered last time
// and goes on to the name entry.  Phase 3 moves over the character grid, 13
// cells a row: the last three cells are space, backspace and end, and end
// writes the replay into the slot.  Phase 4 closes the replays and starts the
// title music after six frames.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update.json).
//
// Equivalent recovery: the two inlined name copies encode [diff+walk] where
// retail has [walk+diff].  The order follows compiler symbol numbers the
// image does not record (reference/recovery_notes/
// replay_save_update_00433570_equivalent_2026_10_11.md).
#include "th10/game/replay_save_update.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem12(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

#pragma code_seg(".text$00433570_fn")
__declspec(noinline) int __stdcall TitleMode16(Title* room) {
    TitleReplaySaveView* save = reinterpret_cast<TitleReplaySaveView*>(room);
    char path[64];
    switch (room->phase) {
    case 0:
        room->cursor.item_count = 25;
        room->cursor.wrap = 1;
        SelectItem12(room->cursor, 0);
        g_stage_route_current = g_stage_routes + 8 * 0x30;
        g_globals_stage = 8;
        g_globals_stage_shown = 8;
        for (int number = 1; number <= 25; ++number) {
            sprintf(path, "th10_%.2d.rpy", number);
            save->replays[number - 1] = ReplayFile_Open(path);
        }
        RecoveryMusicInstallSlot(room, 105);
        room->SetTimerTarget(1);
    case 1:
        if (room->timer.current > 6)
            room->SetTimerTarget(2);
        break;
    case 2: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection)
            g_sound_manager.Queue(12, 0);
        if (g_input_keys_held & 0xa) {
            room->SetTimerTarget(4);
            g_sound_manager.Queue(11, 0);
        } else if (g_input_keys_held & 0x1001) {
            MenuCursor* grid = &save->grid;
            save->selected_replay = cursor->selection;
            SelectItem12(*grid, 0);
            save->grid.item_count = strlen(g_name_entry_grid);
            save->grid.wrap = 1;
            ReplayFileHeader2** header = &g_replay->header;
            time2(&(*header)->date);
            (*header)->stage = 8;
            strcpy(save->name, g_score->last_name);
            save->name_length = 0;
            if (strcmp(save->name, "        ") != 0)
                grid->Advance(-1);
            int length;
            for (length = 8; length > 0; --length) {
                if (save->name[length - 1] != ' ')
                    break;
            }
            save->name_length = length;
            g_sound_manager.Queue(10, 0);
            room->SetTimerTarget(3);
        }
        break;
    }
    case 3: {
        MenuCursor* grid = &save->grid;
        grid->previous_selection = grid->selection;
        if ((short)g_input_keys_raw.InputMaskActive(0x10)) grid->Advance(-13);
        if ((short)g_input_keys_raw.InputMaskActive(0x20)) grid->Advance(13);
        if ((short)g_input_keys_raw.InputMaskActive(0x40)) {
            if (grid->selection % 13 != 0)
                grid->Advance(-1);
            else
                grid->Advance(12);
        }
        if ((short)g_input_keys_raw.InputMaskActive(0x80)) {
            if (grid->selection % 13 != 12)
                grid->Advance(1);
            else
                grid->Advance(-12);
        }
        if (grid->previous_selection != grid->selection)
            g_sound_manager.Queue(12, 0);
        if (g_input_keys_held & 0x1001) {
            const char* characters = g_name_entry_grid;
            int count = strlen(characters);
            int cell = grid->selection;
            if (cell < count - 3) {
                if (save->name_length < 8) {
                    save->name[save->name_length] = characters[cell];
                    ++save->name_length;
                    if (save->name_length >= 8)
                        UpdateBoundedCounter(count - 1, reinterpret_cast<unsigned int*>(grid));
                } else {
                    save->name[save->name_length - 1] = characters[cell];
                }
            } else if (cell == count - 3) {
                if (save->name_length < 8) {
                    save->name[save->name_length] = ' ';
                    ++save->name_length;
                    if (save->name_length >= 8)
                        UpdateBoundedCounter(count - 1, reinterpret_cast<unsigned int*>(grid));
                } else {
                    save->name[save->name_length - 1] = ' ';
                }
            } else if (cell == count - 2) {
                if (save->name_length == 0)
                    break;
                --save->name_length;
                save->name[save->name_length] = ' ';
            } else if (cell == count - 1) {
                g_sound_manager.Queue(0x2c, 0);
                sprintf(path, "th10_%.2d.rpy", room->cursor.selection + 1);
                ReplayFile_Delete(save->replays[room->cursor.selection]);
                ReplayFile_Save(g_replay, path, save->name);
                int slot = room->cursor.selection;
                save->replays[slot] = ReplayFile_Open(path);
                strcpy(g_score->last_name, save->name);
                room->SetTimerTarget(2);
            }
            g_sound_manager.Queue(10, 0);
        }
        if (g_input_keys_held & 0xa) {
            if (save->name_length == 0) {
                room->SetTimerTarget(2);
            } else {
                g_sound_manager.Queue(11, 0);
                --save->name_length;
                save->name[save->name_length] = ' ';
            }
        }
        break;
    }
    case 4:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(105);
            room->SetSlotFrame(0x5a, 8);
            room->SetSlotFrame(0x5b, 8);
            room->ClearAnimationSlot(94);
            RecoveryMusicStopHandle(&room->fallback_handle);
            room->DisableTimerWithOwner(2);
            room->cursor.PopSelection();
            ReplayFile* recorded = g_replay;
            if (recorded != 0) {
                ReplayFile_Destroy(recorded);
                free(recorded);
            }
            Music_Load2(0, "bgm/th10_02.wav");
            Music_Play2(0, 0);
            for (int index = 0; index < 25; ++index) {
                ReplayFile* replay = save->replays[index];
                if (replay != 0) {
                    ReplayFile_Destroy(replay);
                    free(replay);
                }
            }
            memset(save->replays, 0, sizeof(save->replays));
        }
        break;
    }
    return 1;
}
#pragma code_seg()
