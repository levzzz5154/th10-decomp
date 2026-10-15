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
// (layout/ltcg/difficulty_select_update_00430320.json).
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
        timer->speed = &data_00476f78;
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
__declspec(noinline) int __stdcall TitleMode12_004315c0(Title* room) {
    TitleReplayView* replays = reinterpret_cast<TitleReplayView*>(room);
    char path[64];
    ReplayFindData_004315c0 find;
    void* handle;
    switch (room->phase) {
    case 0: {
        room->cursor.item_count = 25;
        UpdateBoundedCounter(data_00491c04, reinterpret_cast<unsigned int*>(&room->cursor));
        data_00491c04 = 0;
        if (reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
                reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10),
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[94])) == 0) {
            RecoveryMusicInstallSlot_0042c670(room, 94);
            void* resource = g_ascii_manager->animation_resource;
            void** result = AnimationManager_CreatePrimaryBack_00448d00(resource, &handle, 8, 15);
            room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
        }
        RecoveryMusicInstallSlot_0042c670(room, 101);
        room->SetTimerTarget(1);
        memset(replays->replays, 0, sizeof(replays->replays));
        for (int number = 1; number <= 25; ++number) {
            sprintf(path, "th10_%.2d.rpy", number);
            replays->replays[number - 1] = ReplayFile_Open_004296f0(path);
        }
        _mkdir("replay");
        _chdir("replay");
        void* search = FindFirstFileA("th10_ud????.rpy", &find);
        if (search != reinterpret_cast<void*>(-1)) {
            for (int index = 25; index < 50; ++index) {
                _chdir("../");
                replays->replays[index] = ReplayFile_Open_004296f0(find.name);
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
        if ((short)data_00474e30.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)data_00474e30.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection)
            data_00492590.Queue(12, 0);
        if (data_00474e36 & 0xa) {
            room->SetTimerTarget(5);
            data_00492590.Queue(11, 0);
        } else if (data_00474e36 & 0x1001) {
            if (replays->replays[cursor->selection] != 0) {
                room->SetTimerTarget(4);
                replays->selected_replay = cursor->selection;
                cursor->PushSelection();
                data_00492590.Queue(10, 0);
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
            if ((short)data_00474e30.InputMaskActive(0x10)) cursor->Advance(-1);
            if ((short)data_00474e30.InputMaskActive(0x20)) cursor->Advance(1);
            if (cursor->previous_selection != cursor->selection)
                data_00492590.Queue(12, 0);
            if (data_00474e36 & 0xa) {
                cursor->PopSelection();
                room->cursor.item_count = 25;
                room->cursor.disabled_count = 0;
                room->SetTimerTarget(2);
                data_00492590.Queue(11, 0);
            } else if (data_00474e36 & 0x1001) {
                replays->selected_stage = cursor->selection;
                room->SetTimerTarget(3);
            }
        }
        break;
    case 3:
        if (room->timer.current == 2) {
            RecoveryAscii_Create_0043c8b0(0x2b, 5, 0x20, 0, 0, 0);
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
        }
        if (room->timer.current >= 32) {
            room->DisableTimerWithOwner(3);
            int stage = replays->selected_stage + 1;
            data_00477848 = data_00474788 + stage * 0x30;
            data_00474c7c = stage;
            data_00474c80 = stage;
            Music_FadeOut(6.0f);
            data_00491fb8 = 12;
            strcpy(data_00477710, replays->replays[replays->selected_replay]->path);
            ReplayFileHeader_004315c0* header = replays->replays[replays->selected_replay]->header;
            data_00474c68 = header->character;
            data_00474c6c = header->shot_type;
            data_00474c74 = header->difficulty;
            data_00491c00 = 2;
            data_00491c04 = replays->selected_replay;
        }
        break;
    case 5:
        if (room->timer.current >= 6) {
            for (int index = 0; index < 50; ++index) {
                ReplayFile_004315c0* replay = replays->replays[index];
                if (replay != 0) {
                    ReplayFile_Destroy_004294a0(replay);
                    free(replay);
                }
            }
            memset(replays->replays, 0, sizeof(replays->replays));
            room->ClearAnimationSlot(101);
            room->SetSlotFrame(0x5a, 8);
            room->SetSlotFrame(0x5b, 8);
            room->ClearAnimationSlot(94);
            RecoveryMusicStopHandle_00409e50(&room->fallback_handle);
            room->DisableTimerWithOwner(2);
            PopSelection_004315c0(room->cursor);
        }
        break;
    }
    return 1;
}
#pragma code_seg()
