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
// Byte-exact native LTCG recovery. Named menu predicates preserve the
// compiler symbol ordering used by both inlined name copies; see
// reference/recovery_notes/replay_save_update_00433570_exact_2026_10_17.md.
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
    Title& screen = *room;
    char path[64];
    switch (screen.phase) {
    case 0:
        screen.cursor.item_count = 25;
        screen.cursor.wrap = 1;
        SelectItem12(screen.cursor, 0);
        g_stage_route_current = g_stage_routes + StageRouteCount;
        g_globals_stage = StageRouteCount;
        g_globals_stage_shown = StageRouteCount;
        for (int number = 1; number <= 25; ++number) {
            sprintf(path, "th10_%.2d.rpy", number);
            screen.replay_list.files[number - 1] = ReplayFile_Open(path);
        }
        RecoveryMusicInstallSlot(room, 105);
        screen.SetTimerTarget(1);
    case 1: {
        const bool opening_delay_done = (screen.timer.current > 6);
        if (opening_delay_done)
            screen.SetTimerTarget(2);
        break;
    }
    case 2: {
        MenuCursor* cursor = &screen.cursor;
        cursor->previous_selection = cursor->selection;
        const bool slot_up = ((short)g_input_keys_raw.InputMaskActive(0x10));
        if (slot_up) cursor->Advance(-1);
        const bool slot_down = ((short)g_input_keys_raw.InputMaskActive(0x20));
        if (slot_down) cursor->Advance(1);
        const bool slot_changed = (cursor->previous_selection != cursor->selection);
        if (slot_changed)
            g_sound_manager.Queue(12, 0);
        const bool cancel_slot = (g_input_keys_held & 0xa);
        if (cancel_slot) {
            screen.SetTimerTarget(4);
            g_sound_manager.Queue(11, 0);
        } else if (g_input_keys_held & 0x1001) {
            MenuCursor* grid = &screen.keyboard.grid;
            screen.replay_list.selected_replay = cursor->selection;
            SelectItem12(*grid, 0);
            screen.keyboard.grid.item_count = strlen(g_name_entry_grid);
            screen.keyboard.grid.wrap = 1;
            ReplayFileHeader2** header = &g_replay->header;
            time2(&(*header)->date);
            (*header)->stage = StageRouteCount;
            strcpy(screen.keyboard.name, g_score->last_name);
            screen.keyboard.name_length = 0;
            const bool has_previous_name = (strcmp(screen.keyboard.name, "        ") != 0);
            if (has_previous_name)
                grid->Advance(-1);
            int length;
            for (length = 8; length > 0; --length) {
                const bool has_name_character = (screen.keyboard.name[length - 1] != ' ');
                if (has_name_character)
                    break;
            }
            screen.keyboard.name_length = length;
            g_sound_manager.Queue(10, 0);
            screen.SetTimerTarget(3);
        }
        break;
    }
    case 3: {
        MenuCursor* grid = &screen.keyboard.grid;
        grid->previous_selection = grid->selection;
        const bool grid_up = ((short)g_input_keys_raw.InputMaskActive(0x10));
        if (grid_up) grid->Advance(-13);
        const bool grid_down = ((short)g_input_keys_raw.InputMaskActive(0x20));
        if (grid_down) grid->Advance(13);
        const bool grid_left = ((short)g_input_keys_raw.InputMaskActive(0x40));
        if (grid_left) {
            const bool can_move_left = (grid->selection % 13 != 0);
            if (can_move_left)
                grid->Advance(-1);
            else
                grid->Advance(12);
        }
        const bool grid_right = ((short)g_input_keys_raw.InputMaskActive(0x80));
        if (grid_right) {
            const bool can_move_right = (grid->selection % 13 != 12);
            if (can_move_right)
                grid->Advance(1);
            else
                grid->Advance(-12);
        }
        const bool grid_changed = (grid->previous_selection != grid->selection);
        if (grid_changed)
            g_sound_manager.Queue(12, 0);
        const bool confirm_character = (g_input_keys_held & 0x1001);
        if (confirm_character) {
            const char* characters = g_name_entry_grid;
            int count = strlen(characters);
            int cell = grid->selection;
            const bool is_character = (cell < count - 3);
            if (is_character) {
                if (screen.keyboard.name_length < 8) {
                    screen.keyboard.name[screen.keyboard.name_length] = characters[cell];
                    ++screen.keyboard.name_length;
                    if (screen.keyboard.name_length >= 8)
                        UpdateBoundedCounter(count - 1, reinterpret_cast<unsigned int*>(grid));
                } else {
                    screen.keyboard.name[screen.keyboard.name_length - 1] = characters[cell];
                }
            } else if (cell == count - 3) {
                if (screen.keyboard.name_length < 8) {
                    screen.keyboard.name[screen.keyboard.name_length] = ' ';
                    ++screen.keyboard.name_length;
                    if (screen.keyboard.name_length >= 8)
                        UpdateBoundedCounter(count - 1, reinterpret_cast<unsigned int*>(grid));
                } else {
                    screen.keyboard.name[screen.keyboard.name_length - 1] = ' ';
                }
            } else if (cell == count - 2) {
                if (screen.keyboard.name_length == 0)
                    break;
                --screen.keyboard.name_length;
                screen.keyboard.name[screen.keyboard.name_length] = ' ';
            } else if (cell == count - 1) {
                g_sound_manager.Queue(0x2c, 0);
                sprintf(path, "th10_%.2d.rpy", screen.cursor.selection + 1);
                ReplayFile_Delete(screen.replay_list.files[screen.cursor.selection]);
                ReplayFile_Save(g_replay, path, screen.keyboard.name);
                int slot = screen.cursor.selection;
                screen.replay_list.files[slot] = ReplayFile_Open(path);
                strcpy(g_score->last_name, screen.keyboard.name);
                screen.SetTimerTarget(2);
            }
            g_sound_manager.Queue(10, 0);
        }
        if (g_input_keys_held & 0xa) {
            if (screen.keyboard.name_length == 0) {
                screen.SetTimerTarget(2);
            } else {
                g_sound_manager.Queue(11, 0);
                --screen.keyboard.name_length;
                screen.keyboard.name[screen.keyboard.name_length] = ' ';
            }
        }
        break;
    }
    case 4:
        if (screen.timer.current >= 6) {
            screen.ClearAnimationSlot(105);
            screen.SetSlotFrame(0x5a, 8);
            screen.SetSlotFrame(0x5b, 8);
            screen.ClearAnimationSlot(94);
            RecoveryMusicStopHandle(&screen.fallback_handle);
            screen.DisableTimerWithOwner(2);
            screen.cursor.PopSelection();
            ReplayFile* recorded = g_replay;
            if (recorded != 0) {
                ReplayFile_Destroy(recorded);
                free(recorded);
            }
            Music_Load2(0, "bgm/th10_02.wav");
            Music_Play2(0, 0);
            for (int index = 0; index < 25; ++index) {
                ReplayFile* replay = screen.replay_list.files[index];
                if (replay != 0) {
                    ReplayFile_Destroy(replay);
                    free(replay);
                }
            }
            memset(screen.replay_list.files, 0, sizeof(screen.replay_list.files));
        }
        break;
    }
    return 1;
}
#pragma code_seg()
