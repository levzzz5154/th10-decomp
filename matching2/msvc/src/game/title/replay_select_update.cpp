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
#include "th10/game/replay_select_update.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem9(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// MenuCursor::DisableItem (0x00434BC0) as it is inlined here.
static __forceinline void DisableItem5(MenuCursor& cursor, int item) {
    cursor.disabled_items[cursor.disabled_count] = item;
    ++cursor.disabled_count;
}

// MenuCursor::PopSelection (0x0044BE70) as it is inlined in phase 5.
static __forceinline void PopSelection2(MenuCursor& cursor) {
    --cursor.history_depth;
    if (cursor.history_depth < 0)
        cursor.history_depth = 0;
    cursor.selection = cursor.selection_history[cursor.history_depth];
    cursor.item_count = cursor.item_count_history[cursor.history_depth];
    cursor.disabled_count = 0;
}

// The timer reset and SetTimerTarget (0x0042C620) as they are inlined in
// phase 1.
static __forceinline void ResetTimer2(RecoveryTimer2* timer) {
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
static __forceinline void SetTimerTarget2(Title* room, int target) {
    room->phase = target;
    ResetTimer2(&room->timer);
}

enum ReplaySelectPhase {
    RSEL_PHASE_ENTER = 0,
    RSEL_PHASE_WAIT_OPEN = 1,
    RSEL_PHASE_PICK_REPLAY = 2,
    RSEL_PHASE_LAUNCH_REPLAY = 3,
    RSEL_PHASE_PICK_STAGE = 4,
    RSEL_PHASE_CANCEL_LEAVE = 5
};

enum ReplaySelectConstants {
    RSEL_NUMBERED_SLOTS = 25,
    RSEL_TOTAL_SLOTS = 50,
    RSEL_STAGE_SLOTS = 7,
    RSEL_KEY_CANCEL = 0x000A,
    RSEL_KEY_UP = 0x0010,
    RSEL_KEY_DOWN = 0x0020,
    RSEL_KEY_CONFIRM = 0x1001,
    RSEL_SFX_CONFIRM = 10,
    RSEL_SFX_CANCEL = 11,
    RSEL_SFX_MOVE = 12,
    RSEL_TARGET_MAIN_MENU = 2,
    RSEL_TARGET_LEAVE = 3,
    RSEL_MAIN_MODE_REPLAY = 12
};

#pragma code_seg(".text$004315c0_fn")
__declspec(noinline) int __stdcall TitleMode12(Title* room) {
    char path[64];
    ReplayFindData find;
    void* handle;
    switch (room->phase) {
    case RSEL_PHASE_ENTER: {
        room->cursor.item_count = RSEL_NUMBERED_SLOTS;
        UpdateBoundedCounter(g_title_replay_selection, reinterpret_cast<unsigned int*>(&room->cursor));
        g_title_replay_selection = 0;
        EnsureTitleMenuBackdrop(room, handle);
        RecoveryMusicInstallSlot(room, 101);
        room->SetTimerTarget(RSEL_PHASE_WAIT_OPEN);
        memset(room->replay_list.files, 0, sizeof(room->replay_list.files));
        for (int number = 1; number <= RSEL_NUMBERED_SLOTS; ++number) {
            sprintf(path, "th10_%.2d.rpy", number);
            room->replay_list.files[number - 1] = ReplayFile_Open(path);
        }
        _mkdir("replay");
        _chdir("replay");
        void* search = FindFirstFileA("th10_ud????.rpy", &find);
        if (search != reinterpret_cast<void*>(-1)) {
            for (int index = RSEL_NUMBERED_SLOTS; index < RSEL_TOTAL_SLOTS; ++index) {
                _chdir("../");
                room->replay_list.files[index] = ReplayFile_Open(find.name);
                _chdir("replay");
                if (!FindNextFileA(search, &find))
                    break;
            }
        }
        FindClose(search);
        _chdir("../");
        room->replay_list.reserved_59d8 = 0;
    }
    case RSEL_PHASE_WAIT_OPEN:
        if (room->timer.current > 6)
            SetTimerTarget2(room, RSEL_PHASE_PICK_REPLAY);
        break;
    case RSEL_PHASE_PICK_REPLAY: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(RSEL_KEY_UP)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(RSEL_KEY_DOWN)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection)
            g_sound_manager.Queue(RSEL_SFX_MOVE, 0);
        if (g_input_keys_held & RSEL_KEY_CANCEL) {
            room->SetTimerTarget(RSEL_PHASE_CANCEL_LEAVE);
            g_sound_manager.Queue(RSEL_SFX_CANCEL, 0);
        } else if (g_input_keys_held & RSEL_KEY_CONFIRM) {
            if (room->replay_list.files[cursor->selection] != 0) {
                room->SetTimerTarget(RSEL_PHASE_PICK_STAGE);
                room->replay_list.selected_replay = cursor->selection;
                cursor->PushSelection();
                g_sound_manager.Queue(RSEL_SFX_CONFIRM, 0);
                room->cursor.item_count = RSEL_STAGE_SLOTS;
                SelectItem9(*cursor, 0);
                int stage = 0;
                do {
                    if (room->replay_list.files[room->replay_list.selected_replay]->stages[stage].recorded == 0)
                        DisableItem5(*cursor, stage);
                    ++stage;
                } while (stage < RSEL_STAGE_SLOTS);
                cursor->Advance(-1);
                cursor->Advance(1);
            }
        }
        break;
    }
    case RSEL_PHASE_PICK_STAGE:
        if (room->timer.current >= 15) {
            MenuCursor* cursor = &room->cursor;
            cursor->previous_selection = cursor->selection;
            if ((short)g_input_keys_raw.InputMaskActive(RSEL_KEY_UP)) cursor->Advance(-1);
            if ((short)g_input_keys_raw.InputMaskActive(RSEL_KEY_DOWN)) cursor->Advance(1);
            if (cursor->previous_selection != cursor->selection)
                g_sound_manager.Queue(RSEL_SFX_MOVE, 0);
            if (g_input_keys_held & RSEL_KEY_CANCEL) {
                cursor->PopSelection();
                room->cursor.item_count = RSEL_NUMBERED_SLOTS;
                room->cursor.disabled_count = 0;
                room->SetTimerTarget(RSEL_PHASE_PICK_REPLAY);
                g_sound_manager.Queue(RSEL_SFX_CANCEL, 0);
            } else if (g_input_keys_held & RSEL_KEY_CONFIRM) {
                room->replay_list.selected_stage = cursor->selection;
                room->SetTimerTarget(RSEL_PHASE_LAUNCH_REPLAY);
            }
        }
        break;
    case RSEL_PHASE_LAUNCH_REPLAY:
        if (room->timer.current == 2) {
            RecoveryAscii_Create(0x2b, 5, 0x20, 0, 0, 0);
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
        }
        if (room->timer.current >= 32) {
            room->DisableTimerWithOwner(RSEL_TARGET_LEAVE);
            int stage = room->replay_list.selected_stage + 1;
            g_stage_route_current = &g_stage_routes[stage];
            g_globals_stage = stage;
            g_globals_stage_shown = stage;
            Music_FadeOut(6.0f);
            g_main_state = RSEL_MAIN_MODE_REPLAY;
            strcpy(g_replay_path, room->replay_list.files[room->replay_list.selected_replay]->path);
            ReplayFileHeader2* header = room->replay_list.files[room->replay_list.selected_replay]->header;
            g_globals_character = header->character;
            g_globals_shot_type = header->shot_type;
            g_globals_difficulty = header->difficulty;
            g_main_mode_request = 2;
            g_title_replay_selection = room->replay_list.selected_replay;
        }
        break;
    case RSEL_PHASE_CANCEL_LEAVE:
        if (room->timer.current >= 6) {
            for (int index = 0; index < RSEL_TOTAL_SLOTS; ++index) {
                ReplayFile* replay = room->replay_list.files[index];
                if (replay != 0) {
                    ReplayFile_Destroy(replay);
                    free(replay);
                }
            }
            memset(room->replay_list.files, 0, sizeof(room->replay_list.files));
            room->ClearAnimationSlot(101);
            room->SetSlotFrame(0x5a, 8);
            room->SetSlotFrame(0x5b, 8);
            room->ClearAnimationSlot(94);
            RecoveryMusicStopHandle(&room->fallback_handle);
            room->DisableTimerWithOwner(RSEL_TARGET_MAIN_MENU);
            PopSelection2(room->cursor);
        }
        break;
    }
    return 1;
}
#pragma code_seg()
