// 0x004315C0..0x00431B93: replay selection screen of the title menu (and its
// six-entry phase table).
//
// Phase 0 opens the 25 numbered replays and up to 25 user-named ones from the
// replay directory, puts the cursor on the replay chosen last time and runs
// phase 1 on the same frame.  Phase 1 waits seven frames.  Phase 2 picks a
// replay; confirm on an existing one goes on to its stages, with the stages
// the replay does not hold disabled.  Phase 4 picks the stage, phase 3 starts
// the playback after 32 frames, and phase 5 closes the replays and goes back
// to the main menu after six.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update.json).
#include "th10/game/replay_select_update_004315c0.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem_004315c0(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// MenuCursor::DisableItem (0x00434BC0) as it is inlined here.
static __forceinline void DisableItem_004315c0(MenuCursor& cursor, int item) {
    cursor.disabled_items[cursor.disabled_count] = item;
    ++cursor.disabled_count;
}

// MenuCursor::PopSelection (0x0044BE70) as it is inlined in phase 5.
static __forceinline void PopSelection_004315c0(MenuCursor& cursor) {
    --cursor.history_depth;
    if (cursor.history_depth < 0)
        cursor.history_depth = 0;
    cursor.selection = cursor.selection_history[cursor.history_depth];
    cursor.item_count = cursor.item_count_history[cursor.history_depth];
    cursor.disabled_count = 0;
}

// The timer reset and SetTimerTarget (0x0042C620) as they are inlined in
// phase 1.
static __forceinline void ResetTimer_004315c0(RecoveryTimer_0040bd80* timer) {
    if (!(timer->flags & 1u)) {
        timer->current = 0;
        timer->previous = -999999;
        timer->elapsed = 0;
        timer->speed = &g_game_speed;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->elapsed = 0;
    timer->previous = -1;
}
static __forceinline void SetTimerTarget_004315c0(Title* room, int target) {
    room->phase = target;
    ResetTimer_004315c0(&room->timer);
}

#pragma code_seg(".text$004315c0_fn")
__declspec(noinline) int __stdcall TitleMode12(Title* room) {
    TitleReplayView* replays = reinterpret_cast<TitleReplayView*>(room);
    char path[64];
    ReplayFindData find;
    void* handle;
    switch (room->phase) {
    case 0: {
        room->cursor.item_count = 25;
        UpdateBoundedCounter(g_title_replay_selection, reinterpret_cast<unsigned int*>(&room->cursor));
        g_title_replay_selection = 0;
        if (reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(
                reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId*>(&room->animation_slots[94])) == 0) {
            RecoveryMusicInstallSlot(room, 94);
            void* resource = g_ascii_manager->animation_resource;
            void** result = AnimationManager_CreatePrimaryBack(resource, &handle, 8, 15);
            room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
        }
        RecoveryMusicInstallSlot(room, 101);
        room->SetTimerTarget(1);
        memset(replays->replays, 0, sizeof(replays->replays));
        for (int number = 1; number <= 25; ++number) {
            sprintf(path, "th10_%.2d.rpy", number);
            replays->replays[number - 1] = ReplayFile_Open(path);
        }
        _mkdir("replay");
        _chdir("replay");
        void* search = FindFirstFileA("th10_ud????.rpy", &find);
        if (search != reinterpret_cast<void*>(-1)) {
            for (int index = 25; index < 50; ++index) {
                _chdir("../");
                replays->replays[index] = ReplayFile_Open(find.name);
                _chdir("replay");
                if (!FindNextFileA(search, &find))
                    break;
            }
        }
        FindClose(search);
        _chdir("../");
        replays->reserved_59d8 = 0;
    }
    case 1:
        if (room->timer.current > 6)
            SetTimerTarget_004315c0(room, 2);
        break;
    case 2: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection)
            g_sound_manager.Queue(12, 0);
        if (g_input_keys_held & 0xa) {
            room->SetTimerTarget(5);
            g_sound_manager.Queue(11, 0);
        } else if (g_input_keys_held & 0x1001) {
            if (replays->replays[cursor->selection] != 0) {
                room->SetTimerTarget(4);
                replays->selected_replay = cursor->selection;
                cursor->PushSelection();
                g_sound_manager.Queue(10, 0);
                room->cursor.item_count = 7;
                SelectItem_004315c0(*cursor, 0);
                int stage = 0;
                do {
                    if (replays->replays[replays->selected_replay]->stages[stage].recorded == 0)
                        DisableItem_004315c0(*cursor, stage);
                    ++stage;
                } while (stage < 7);
                cursor->Advance(-1);
                cursor->Advance(1);
            }
        }
        break;
    }
    case 4:
        if (room->timer.current >= 15) {
            MenuCursor* cursor = &room->cursor;
            cursor->previous_selection = cursor->selection;
            if ((short)g_input_keys_raw.InputMaskActive(0x10)) cursor->Advance(-1);
            if ((short)g_input_keys_raw.InputMaskActive(0x20)) cursor->Advance(1);
            if (cursor->previous_selection != cursor->selection)
                g_sound_manager.Queue(12, 0);
            if (g_input_keys_held & 0xa) {
                cursor->PopSelection();
                room->cursor.item_count = 25;
                room->cursor.disabled_count = 0;
                room->SetTimerTarget(2);
                g_sound_manager.Queue(11, 0);
            } else if (g_input_keys_held & 0x1001) {
                replays->selected_stage = cursor->selection;
                room->SetTimerTarget(3);
            }
        }
        break;
    case 3:
        if (room->timer.current == 2) {
            RecoveryAscii_Create(0x2b, 5, 0x20, 0, 0, 0);
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
        }
        if (room->timer.current >= 32) {
            room->DisableTimerWithOwner(3);
            int stage = replays->selected_stage + 1;
            g_stage_route_current = g_stage_routes + stage * 0x30;
            g_globals_stage = stage;
            g_globals_stage_shown = stage;
            Music_FadeOut(6.0f);
            g_main_state = 12;
            strcpy(g_replay_path, replays->replays[replays->selected_replay]->path);
            ReplayFileHeader_004315c0* header = replays->replays[replays->selected_replay]->header;
            g_globals_character = header->character;
            g_globals_shot_type = header->shot_type;
            g_globals_difficulty = header->difficulty;
            g_main_mode_request = 2;
            g_title_replay_selection = replays->selected_replay;
        }
        break;
    case 5:
        if (room->timer.current >= 6) {
            for (int index = 0; index < 50; ++index) {
                ReplayFile_004315c0* replay = replays->replays[index];
                if (replay != 0) {
                    ReplayFile_Destroy(replay);
                    free(replay);
                }
            }
            memset(replays->replays, 0, sizeof(replays->replays));
            room->ClearAnimationSlot(101);
            room->SetSlotFrame(0x5a, 8);
            room->SetSlotFrame(0x5b, 8);
            room->ClearAnimationSlot(94);
            RecoveryMusicStopHandle(&room->fallback_handle);
            room->DisableTimerWithOwner(2);
            PopSelection_004315c0(room->cursor);
        }
        break;
    }
    return 1;
}
#pragma code_seg()
