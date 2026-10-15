// 0x00432CB0..0x00433227: high score name entry of the title menu (and its
// four-entry phase table), shown after a game that was not a replay.
//
// Phase 0 starts the score music, shows the character, shot type and
// difficulty of the game and enters the score into its table.  With a rank
// the cursor goes to the new line and the name entered last time is
// proposed; without one there is nothing to type and any button leaves.
// Phase 1 waits seven frames.  Phase 2 moves over the character grid, 13
// cells a row: the last three cells are space, backspace and end, and end
// stores the name.  Phase 3 removes the screen after six frames.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update_00430320.json).
//
// Equivalent recovery: retail keeps the created handle in a stack slot of its
// own (push ecx at entry), this build puts it in the dead argument slot
// (reference/recovery_notes/name_entry_update_00432cb0_equivalent_2026_10_11.md).
#include "th10/game/name_entry_update_00432cb0.hpp"

// Select an item, clamped to the items of the menu when it has any.
static __forceinline void SelectItem_00432cb0(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : ((index < 0) - 1) & index;
    else
        cursor.selection = index;
}

// The score file with its high-score tables.
static __forceinline NameEntryScoreFile_00432cb0* ScoreFile_00432cb0() {
    return reinterpret_cast<NameEntryScoreFile_00432cb0*>(g_score);
}

#pragma code_seg(".text$00432cb0_fn")
__declspec(noinline) int __stdcall TitleNameEntry_00432cb0(Title* room) {
    TitleReplaySaveView* entry = reinterpret_cast<TitleReplaySaveView*>(room);
    void* handle;
    switch (room->phase) {
    case 0: {
        room->cursor.item_count = 30;
        Music_Load_00420a90(0, "bgm/th10_17.wav");
        Music_Play_00420b10(0, 17);
        if (reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(
                reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[94])) == 0) {
            RecoveryMusicInstallSlot_0042c670(room, 94);
            void* resource = g_ascii_manager->animation_resource;
            void** result = AnimationManager_CreatePrimaryBack_00448d00(resource, &handle, 8, 15);
            room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
        }
        RecoveryMusicInstallSlot_0042c670(room, 104);
        room->SetTimerTarget(1);
        RecoveryMusicInstallSlot_0042c670(room, g_globals_character + 152);
        RecoveryMusicInstallSlot_0042c670(room, g_globals_character * 3 + g_globals_shot_type + 154);
        RecoveryMusicInstallSlot_0042c670(room, g_globals_difficulty + 160);
        // The table records the stage of a whole game.
        g_globals_stage = 8;
        g_globals_stage_shown = 8;
        g_stage_route_current = g_stage_routes + 8 * 0x30;
        int rank = ScoreFile_00432cb0()->shots[g_globals_character][g_globals_shot_type].table.InsertScore();
        g_stage_route_current = g_stage_routes;
        g_globals_stage = 0;
        g_globals_stage_shown = 0;
        if (rank >= 0) {
            room->timer.Set(0);
            room->cursor.wrap = 1;
            UpdateBoundedCounter(rank, reinterpret_cast<unsigned int*>(&room->cursor));
            MenuCursor* grid = &entry->grid;
            SelectItem_00432cb0(*grid, 0);
            entry->grid.item_count = strlen(g_name_entry_grid);
            entry->grid.wrap = 1;
            strcpy(entry->name, g_score->last_name);
            if (strcmp(entry->name, "        ") != 0)
                grid->Advance(-1);
            int length;
            for (length = 8; length > 0; --length) {
                if (entry->name[length - 1] != ' ')
                    break;
            }
            entry->name_length = length;
            entry->name_confirmed = 0;
        } else {
            SelectItem_00432cb0(room->cursor, -1);
            entry->name_confirmed = 1;
        }
    }
    case 1:
        if (room->timer.current > 6)
            room->SetTimerTarget(2);
        break;
    case 2:
        if (entry->name_confirmed == 0) {
            KeyRepeatState* input = &g_input_keys_raw;
            MenuCursor* grid = &entry->grid;
            grid->previous_selection = grid->selection;
            if ((short)input->InputMaskActive(0x10)) grid->Advance(-13);
            if ((short)input->InputMaskActive(0x20)) grid->Advance(13);
            if ((short)input->InputMaskActive(0x40)) {
                if (grid->selection % 13 != 0)
                    grid->Advance(-1);
                else
                    grid->Advance(12);
            }
            if ((short)input->InputMaskActive(0x80)) {
                if (grid->selection % 13 != 12)
                    grid->Advance(1);
                else
                    grid->Advance(-12);
            }
            if (grid->previous_selection != grid->selection)
                g_sound_manager.Queue(12, 0);
        }
        if (g_input_keys_held & 0x1001) {
            if (entry->name_confirmed == 0) {
                const char* characters = g_name_entry_grid;
                int count = strlen(characters);
                int cell = entry->grid.selection;
                if (cell < count - 3) {
                    if (entry->name_length < 8) {
                        entry->name[entry->name_length] = characters[cell];
                        ++entry->name_length;
                        if (entry->name_length >= 8)
                            UpdateBoundedCounter(count - 1, reinterpret_cast<unsigned int*>(&entry->grid));
                    } else {
                        entry->name[entry->name_length - 1] = characters[cell];
                    }
                    g_sound_manager.Queue(10, 0);
                } else if (cell == count - 3) {
                    if (entry->name_length < 8) {
                        entry->name[entry->name_length] = ' ';
                        ++entry->name_length;
                        if (entry->name_length >= 8)
                            UpdateBoundedCounter(count - 1, reinterpret_cast<unsigned int*>(&entry->grid));
                    } else {
                        entry->name[entry->name_length - 1] = ' ';
                    }
                    g_sound_manager.Queue(10, 0);
                } else if (cell == count - 2) {
                    if (entry->name_length == 0)
                        break;
                    --entry->name_length;
                    entry->name[entry->name_length] = ' ';
                    g_sound_manager.Queue(10, 0);
                } else if (cell == count - 1) {
                    strcpy(ScoreFile_00432cb0()->shots[g_globals_character][g_globals_shot_type]
                               .table.records[g_globals_difficulty][room->cursor.selection].name,
                           entry->name);
                    strcpy(ScoreFile_00432cb0()->last_name, entry->name);
                    room->SetTimerTarget(3);
                    g_sound_manager.Queue(10, 0);
                } else {
                    g_sound_manager.Queue(10, 0);
                }
            } else {
                room->SetTimerTarget(3);
                g_sound_manager.Queue(10, 0);
            }
        }
        if (g_input_keys_held & 0xa) {
            if (entry->name_confirmed == 0) {
                if (entry->name_length == 0)
                    break;
                g_sound_manager.Queue(11, 0);
                --entry->name_length;
                entry->name[entry->name_length] = ' ';
            } else {
                room->SetTimerTarget(3);
                g_sound_manager.Queue(10, 0);
            }
        }
        break;
    case 3:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(104);
            room->ClearAnimationSlot(g_globals_character + 152);
            room->ClearAnimationSlot(g_globals_character * 3 + g_globals_shot_type + 154);
            room->ClearAnimationSlot(g_globals_difficulty + 160);
            room->DisableTimerWithOwner(16);
        }
        break;
    }
    return 1;
}
#pragma code_seg()
