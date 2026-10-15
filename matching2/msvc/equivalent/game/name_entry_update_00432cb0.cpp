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
// (layout/ltcg/difficulty_select_update_00430320.json).
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
    return reinterpret_cast<NameEntryScoreFile_00432cb0*>(data_0047783c);
}

#pragma code_seg(".text$00432cb0_fn")
__declspec(noinline) int __stdcall TitleNameEntry_00432cb0(RecoveryMusicRoom_00433ef0* room) {
    ReplaySaveRoom_00433570* entry = reinterpret_cast<ReplaySaveRoom_00433570*>(room);
    void* handle;
    switch (room->phase) {
    case 0: {
        room->cursor.item_count = 30;
        Music_Load_00420a90(0, "bgm/th10_17.wav");
        Music_Play_00420b10(0, 17);
        if (reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
                reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[94])) == 0) {
            RecoveryMusicInstallSlot_0042c670(room, 94);
            void* resource = g_ascii_manager->animation_resource;
            void** result = AnimationManager_CreatePrimaryBack_00448d00(resource, &handle, 8, 15);
            room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
        }
        RecoveryMusicInstallSlot_0042c670(room, 104);
        room->SetTimerTarget(1);
        RecoveryMusicInstallSlot_0042c670(room, data_00474c68 + 152);
        RecoveryMusicInstallSlot_0042c670(room, data_00474c68 * 3 + data_00474c6c + 154);
        RecoveryMusicInstallSlot_0042c670(room, data_00474c74 + 160);
        // The table records the stage of a whole game.
        data_00474c7c = 8;
        data_00474c80 = 8;
        data_00477848 = data_00474788 + 8 * 0x30;
        int rank = ScoreFile_00432cb0()->shots[data_00474c68][data_00474c6c].table.InsertScore();
        data_00477848 = data_00474788;
        data_00474c7c = 0;
        data_00474c80 = 0;
        if (rank >= 0) {
            room->timer.Set(0);
            room->cursor.wrap = 1;
            UpdateBoundedCounter(rank, reinterpret_cast<unsigned int*>(&room->cursor));
            MenuCursor* grid = &entry->grid;
            SelectItem_00432cb0(*grid, 0);
            entry->grid.item_count = strlen(data_004746d8);
            entry->grid.wrap = 1;
            strcpy(entry->name, data_0047783c->last_name);
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
            KeyRepeatState* input = &data_00474e30;
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
                data_00492590.Queue(12, 0);
        }
        if (data_00474e36 & 0x1001) {
            if (entry->name_confirmed == 0) {
                const char* characters = data_004746d8;
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
                    data_00492590.Queue(10, 0);
                } else if (cell == count - 3) {
                    if (entry->name_length < 8) {
                        entry->name[entry->name_length] = ' ';
                        ++entry->name_length;
                        if (entry->name_length >= 8)
                            UpdateBoundedCounter(count - 1, reinterpret_cast<unsigned int*>(&entry->grid));
                    } else {
                        entry->name[entry->name_length - 1] = ' ';
                    }
                    data_00492590.Queue(10, 0);
                } else if (cell == count - 2) {
                    if (entry->name_length == 0)
                        break;
                    --entry->name_length;
                    entry->name[entry->name_length] = ' ';
                    data_00492590.Queue(10, 0);
                } else if (cell == count - 1) {
                    strcpy(ScoreFile_00432cb0()->shots[data_00474c68][data_00474c6c]
                               .table.records[data_00474c74][room->cursor.selection].name,
                           entry->name);
                    strcpy(ScoreFile_00432cb0()->last_name, entry->name);
                    room->SetTimerTarget(3);
                    data_00492590.Queue(10, 0);
                } else {
                    data_00492590.Queue(10, 0);
                }
            } else {
                room->SetTimerTarget(3);
                data_00492590.Queue(10, 0);
            }
        }
        if (data_00474e36 & 0xa) {
            if (entry->name_confirmed == 0) {
                if (entry->name_length == 0)
                    break;
                data_00492590.Queue(11, 0);
                --entry->name_length;
                entry->name[entry->name_length] = ' ';
            } else {
                room->SetTimerTarget(3);
                data_00492590.Queue(10, 0);
            }
        }
        break;
    case 3:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(104);
            room->ClearAnimationSlot(data_00474c68 + 152);
            room->ClearAnimationSlot(data_00474c68 * 3 + data_00474c6c + 154);
            room->ClearAnimationSlot(data_00474c74 + 160);
            room->DisableTimerWithOwner(16);
        }
        break;
    }
    return 1;
}
#pragma code_seg()
