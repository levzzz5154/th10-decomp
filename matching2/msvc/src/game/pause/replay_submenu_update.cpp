// 0x004236F0 - the replay/result submenu dispatch (states 6..13 of the result
// screen record). One state pointer on the stack, RET 4; the record is the
// retail `this`, carrying the two MenuCursors (score rows at +0x24, character
// grid at +0xFC), the +0x1D4 animation handle, the 25 replay-slot managers at
// +0x1EC and the typed name at +0x2B4.
//
// State 6  waits for the entry delay and confirms; state 7 sets up the
// score/name entry (ranking gate publishes the high score); state 8 is the
// three-row save choice; state A browses the 25 replay rows; states B/C are
// the 13-column keyboard editor (plain and alternate); state D dispatches the
// final choice.
#include "th10/game/replay_submenu/state.hpp"

// The repeat-state twin the row screens poll: the 0x474E36 word first, then
// the pressed-edge byte at 0x474E34.
__forceinline short ChoiceInputActive(const KeyRepeatState* input, unsigned short mask) {
    if ((input->unknown_06 & mask) != 0) return 1;
    if ((input->pressed & mask) != 0) return 1;
    return 0;
}

// Select an item, keeping the selection inside a non-empty list.
__forceinline void SelectInList(SubmenuCursor* cursor, int item) {
    if (cursor->item_count != 0)
        cursor->selection = item >= cursor->item_count ? cursor->item_count - 1 : item;
    else
        cursor->selection = item;
}

enum SubmenuStateId {
    SUBMENU_WAIT_ENTRY = 6,
    SUBMENU_SETUP_SCORE = 7,
    SUBMENU_SAVE_CHOICE = 8,
    SUBMENU_REPLAY_BROWSER = 10,
    SUBMENU_REPLAY_NAME_EDITOR = 11,
    SUBMENU_SCORE_NAME_EDITOR = 12,
    SUBMENU_FINAL_EXIT = 13,
    SUBMENU_CLOSED = 21
};

enum SubmenuKeyMask {
    KEY_CONFIRM = 0x1001,
    KEY_CANCEL = 0x000A,
    KEY_UP = 0x0010,
    KEY_DOWN = 0x0020,
    KEY_LEFT = 0x0040,
    KEY_RIGHT = 0x0080
};

enum SubmenuSfxId {
    SFX_CONFIRM = 10,
    SFX_CANCEL = 11,
    SFX_MOVE = 12,
    SFX_REPLAY_SAVED = 44
};

#pragma code_seg(".text$02h")
// MATCH: named single-use bool predicates (e.g. `entry_delay`, `rows_up`)
// reach retail's OptCmpHashVal symbol-table slab so MSVC selects identical SIB bytes.
extern "C" __declspec(noinline) void __stdcall SubmenuUpdate(SubmenuState* state) {
    char path[64];
    switch (state->state) {
    case SUBMENU_WAIT_ENTRY:
        // The confirm gate: after ten ticks, sound 10 and start the setup.
        { bool entry_delay = state->timer.field_04 < 10;
        if (entry_delay) break; }
        { bool gate_idle = (g_input_keys_held & KEY_CONFIRM) == 0;
        if (gate_idle) break; }
        g_sound_manager.Queue(SFX_CONFIRM, 0);
        state->state = SUBMENU_SETUP_SCORE;
        state->background.SetStopFrame(2);
        state->timer.SetSchedulerValue(0);
        return;
    case SUBMENU_SETUP_SCORE:
        { bool setup_delay = state->timer.field_04 < 10;
        if (setup_delay) break; }
        SubUpdateFrameMaximum(g_front);
        if ((g_globals_flags & 0x10) != 0) {
            // Ranking gate: publish the frame-maximum high score into the
            // stage/mode/subslot/difficulty slot of the score file.
            int* slot = reinterpret_cast<int*>(reinterpret_cast<char*>(g_score)
                + (g_globals_shot_type + 3 * g_globals_character) * 0x437C
                + (g_globals_stage + 6 * g_globals_difficulty) * 8 + 0x4DC);
            bool new_high_score = g_globals_score.score > *slot;
            if (new_high_score)
                *slot = g_globals_score.score;
            state->state = SUBMENU_SAVE_CHOICE;
            state->rows.item_count = 3;
            state->rows.wrap = 1;
            SelectInList(&state->rows, 2);
            state->background.StopAtFrame3();
            state->background.SetStopFrame((unsigned short)(state->rows.selection + 7));
            return;
        }
        PrepareNameEntry(reinterpret_cast<NameEntryMenu*>(state));
        state->timer.SetSchedulerValue(0);
        { bool plain_entry = state->no_entry == 0;
        if (plain_entry) {
            state->state = SUBMENU_SCORE_NAME_EDITOR;
            reinterpret_cast<SubAnimNode&>(state->background).ClearFlag();
            return;
        } }
        state->state = SUBMENU_SAVE_CHOICE;
        state->rows.item_count = 3;
        state->rows.wrap = 1;
        SelectInList(&state->rows, 2);
        state->background.StopAtFrame3();
        state->background.SetStopFrame((unsigned short)(state->rows.selection + 7));
        return;
    case SUBMENU_SAVE_CHOICE: {
        // The save choice: navigate, confirm into the replay browser or the
        // alternate flow, cancel back to the three rows.
        SubmenuCursor* rows = &state->rows;
        rows->previous_selection = rows->selection;
        bool rows_up = ChoiceInputActive(&g_input_keys_raw, KEY_UP) != 0;
        if (rows_up)
            rows->Advance(-1);
        bool rows_down = ChoiceInputActive(&g_input_keys_raw, KEY_DOWN) != 0;
        if (rows_down)
            rows->Advance(1);
        bool rows_moved = rows->previous_selection != rows->selection;
        if (rows_moved) {
            state->background.SetStopFrame((unsigned short)rows->selection + 7);
            g_sound_manager.Queue(SFX_MOVE, 0);
        }
        bool rows_confirm = (g_input_keys_held & KEY_CONFIRM) != 0;
        if (rows_confirm) {
            // The rows selection is derived at each live point: the child
            // lookup id here and the dispatch switch after the setup calls
            // (retail reads the cursor twice).
            int id = rows->selection;
            state->background.FindChildRef(id + 0x7C).StopAtFrame6();
            g_sound_manager.Queue(SFX_CONFIRM, 0);
            state->state = SUBMENU_FINAL_EXIT;
            state->timer.SetSchedulerValue(0);
            SubUpdateFrameMaximum(g_front);
            id = rows->selection;
            switch (id) {
            case 1:
                state->state = SUBMENU_REPLAY_BROWSER;
                state->timer.SetSchedulerValue(0);
                reinterpret_cast<SubAnimNode&>(state->background).ClearFlag();
                rows->PushSelection();
                state->rows.item_count = 25;
                state->rows.wrap = 1;
                SelectInList(rows, 0);
                for (int slot = 1; slot <= 25; ++slot) {
                    asm_sprintf_00452ae8(path, "th10_%.2d.rpy", slot);
                    state->handles[slot - 1] = ReplayManager_Create3(path);
                }
            break;
            case 2:
                state->state = SUBMENU_FINAL_EXIT;
                state->timer.SetSchedulerValue(0);
                g_sound_manager.Queue(SFX_CONFIRM, 0);
                break;
            }
        }
        bool rows_cancel = (g_input_keys_held & KEY_CANCEL) != 0;
        if (rows_cancel) {
            g_sound_manager.Queue(SFX_CANCEL, 0);
            bool not_cancel_row = rows->selection != 2;
            if (not_cancel_row) {
                SelectInList(rows, 2);
                state->background.SetStopFrame((short)rows->selection + 7);
            }
        }
        return;
    }
    case SUBMENU_REPLAY_BROWSER:
        // Replay-row browsing over the rows cursor; confirming hands the
        // shared list cursor over to the keyboard editor.
        { bool browser_delay = state->timer.field_04 < 10;
        if (browser_delay) break; }
        {
        SubmenuCursor* rows = &state->rows;
        rows->previous_selection = rows->selection;
        bool browser_up = (short)g_input_keys_raw.InputMaskActive(KEY_UP) != 0;
        if (browser_up)
            rows->Advance(-1);
        bool browser_down = (short)g_input_keys_raw.InputMaskActive(KEY_DOWN) != 0;
        if (browser_down)
            rows->Advance(1);
        bool browser_moved = rows->previous_selection != rows->selection;
        if (browser_moved)
            g_sound_manager.Queue(SFX_MOVE, 0);
        bool browser_confirm = (g_input_keys_held & KEY_CONFIRM) != 0;
        if (browser_confirm) {
            state->state = SUBMENU_REPLAY_NAME_EDITOR;
            state->timer.SetSchedulerValue(0);
            SubmenuCursor* list = &state->list;
            SelectInList(list, 0);
            state->list.item_count = (int)strlen(g_name_entry_grid);
            state->list.wrap = 1;
            bool clear_ranking = state->extra_cleared != 0 && (g_globals_flags & 0x10) == 0;
            if (clear_ranking) {
                ReplayHeaderView*& summary =
                    reinterpret_cast<ReplayHeaderView*&>(g_replay->summary);
                asm_FID_conflict___time32_00452b71(&summary->saved_time);
                summary->difficulty_slot = 8;
            } else {
                ReplayHeaderView*& summary =
                    reinterpret_cast<ReplayHeaderView*&>(g_replay->summary);
                asm_FID_conflict___time32_00452b71(&summary->saved_time);
                summary->difficulty_slot = g_globals_stage;
            }
            strcpy(state->name, g_score->last_name);
            state->name_length = 0;
            bool custom_name = strcmp(state->name, "        ") != 0;
            if (custom_name)
                list->Advance(-1);
            int length = 8;
            do {
                bool trim_not_space = state->name[length - 1] != ' ';
                if (trim_not_space)
                    goto timed_length;
                --length;
            } while (length > 0);
timed_length:
            state->name_length = length;
            g_sound_manager.Queue(SFX_CONFIRM, 0);
            return;
        }
        bool browser_cancel = (g_input_keys_held & KEY_CANCEL) != 0;
        if (browser_cancel) {
            // Cancel: release the 25 replay managers and restore the rows.
            state->state = SUBMENU_SAVE_CHOICE;
            state->timer.SetSchedulerValue(0);
            reinterpret_cast<SubAnimNode&>(state->background).SetFlag();
            state->rows.PopSelection();
            state->rows.item_count = 3;
            state->rows.wrap = 1;
            state->background.SetStopFrame((short)state->rows.selection + 7);
            for (int index = 0; index < 25; ++index) {
                void* handle = state->handles[index];
                bool live_handle = handle != 0;
                if (live_handle) {
                    ReplayManager_Destroy2(handle);
                    asm_free_004524a1(handle);
                }
                state->handles[index] = 0;
            }
            state->state = SUBMENU_SAVE_CHOICE;
            state->timer.SetSchedulerValue(0);
            g_sound_manager.Queue(SFX_CANCEL, 0);
        }
        return;
    }
    case SUBMENU_REPLAY_NAME_EDITOR: {
        // The 13-column keyboard editor: letters, space, backspace, save.
        bool editor_delay = state->timer.field_04 < 10;
        if (editor_delay) break;
        SubmenuCursor* list = &state->list;
        list->previous_selection = list->selection;
        bool editor_up = (short)g_input_keys_raw.InputMaskActive(KEY_UP) != 0;
        if (editor_up)
            list->Advance(-13);
        bool editor_down = (short)g_input_keys_raw.InputMaskActive(KEY_DOWN) != 0;
        if (editor_down)
            list->Advance(13);
        bool editor_left = (short)g_input_keys_raw.InputMaskActive(KEY_LEFT) != 0;
        if (editor_left) {
            if (list->selection % 13)
                list->Advance(-1);
            else
                list->Advance(12);
        }
        bool editor_right = (short)g_input_keys_raw.InputMaskActive(KEY_RIGHT) != 0;
        if (editor_right) {
            if (list->selection % 13 != 12)
                list->Advance(1);
            else
                list->Advance(-12);
        }
        bool editor_moved = list->previous_selection != list->selection;
        if (editor_moved)
            g_sound_manager.Queue(SFX_MOVE, 0);
        bool editor_confirm = (g_input_keys_held & KEY_CONFIRM) != 0;
        if (editor_confirm) {
            const char* grid = g_name_entry_grid;
            int length = (int)strlen(grid);
            int selection = list->selection;
            bool letter_cell = selection < length - 3;
            if (letter_cell) {
                bool room_left = state->name_length < 8;
                if (room_left) {
                    state->name[state->name_length] = grid[selection];
                    ++state->name_length;
                    if (state->name_length >= 8)
                        UpdateBoundedCounter(length - 1, (unsigned int*)&list->selection);
                } else {
                    state->name[state->name_length - 1] = grid[selection];
                }
            } else if (selection == length - 3) {
                bool space_room = state->name_length < 8;
                if (space_room) {
                    state->name[state->name_length] = ' ';
                    ++state->name_length;
                    if (state->name_length >= 8)
                        UpdateBoundedCounter(length - 1, (unsigned int*)&list->selection);
                } else {
                    state->name[state->name_length - 1] = ' ';
                }
            } else if (selection == length - 2) {
                bool empty_name = state->name_length == 0;
                if (empty_name)
                    return;
                --state->name_length;
                state->name[state->name_length] = ' ';
                g_sound_manager.Queue(SFX_CANCEL, 0);
                return;
            } else if (selection == length - 1) {
                // The save column: serialize the replay under the typed name.
                g_sound_manager.Queue(SFX_REPLAY_SAVED, 0);
                asm_sprintf_00452ae8(path, "th10_%.2d.rpy", state->rows.selection + 1);
                SubPlatformResource_Destroy(
                    reinterpret_cast<PlatformResource*>(state->handles[state->rows.selection]));
                asm_FUN_00429b60_00429b60(g_replay, path, state->name);
                int save_row = state->rows.selection;
                state->handles[save_row] = ReplayManager_Create3(path);
                state->state = SUBMENU_REPLAY_BROWSER;
                state->timer.SetSchedulerValue(0);
                strcpy(g_score->last_name, state->name);
                return;
            }
            // The letter/space cells queue the append sound and fall through
            // to the cancel test in the same frame.
            g_sound_manager.Queue(SFX_CONFIRM, 0);
        }
        bool editor_cancel = (g_input_keys_held & KEY_CANCEL) != 0;
        if (editor_cancel) {
            g_sound_manager.Queue(SFX_CANCEL, 0);
            bool has_letters = state->name_length != 0;
            if (!has_letters) {
                state->state = SUBMENU_REPLAY_BROWSER;
                state->timer.SetSchedulerValue(0);
            } else {
                --state->name_length;
                state->name[state->name_length] = ' ';
                return;
            }
        }
        return;
    }
    case SUBMENU_SCORE_NAME_EDITOR: {
        // The alternate keyboard path; the no_entry latch swaps the editing
        // pass for the task re-registration.
        if (state->timer.field_04 < 10) break;
        bool plain_editing = state->no_entry == 0;
        if (plain_editing) {
            SubmenuCursor* list = &state->list;
            list->previous_selection = list->selection;
            if ((short)g_input_keys_raw.InputMaskActive(KEY_UP))
                list->Advance(-13);
            if ((short)g_input_keys_raw.InputMaskActive(KEY_DOWN))
                list->Advance(13);
            if ((short)g_input_keys_raw.InputMaskActive(KEY_LEFT)) {
                if (list->selection % 13)
                    list->Advance(-1);
                else
                    list->Advance(12);
            }
            if ((short)g_input_keys_raw.InputMaskActive(KEY_RIGHT)) {
                if (list->selection % 13 != 12)
                    list->Advance(1);
                else
                    list->Advance(-12);
            }
            if (list->previous_selection != list->selection)
                g_sound_manager.Queue(SFX_MOVE, 0);
        }
        bool editor_confirm = (g_input_keys_held & KEY_CONFIRM) != 0;
        if (editor_confirm) {
            if (state->no_entry == 0) {
                const char* grid = g_name_entry_grid;
                int length = (int)strlen(grid);
                int selection = state->list.selection;
                if (selection < length - 3) {
                    if (state->name_length < 8) {
                        state->name[state->name_length] = grid[selection];
                        ++state->name_length;
                        if (state->name_length >= 8)
                            UpdateBoundedCounter(length - 1, (unsigned int*)&state->list.selection);
                    } else {
                        state->name[state->name_length - 1] = grid[selection];
                    }
                } else if (selection == length - 3) {
                    if (state->name_length < 8) {
                        state->name[state->name_length] = ' ';
                        ++state->name_length;
                        if (state->name_length >= 8)
                            UpdateBoundedCounter(length - 1, (unsigned int*)&state->list.selection);
                    } else {
                        state->name[state->name_length - 1] = ' ';
                    }
                } else if (selection == length - 2) {
                    if (state->name_length == 0)
                        return;
                    --state->name_length;
                    state->name[state->name_length] = ' ';
                } else if (selection == length - 1) {
                    // Save the name into the stage/mode/subslot slot table.
                    char* slot = reinterpret_cast<char*>(g_score)
                        + (g_globals_shot_type + 3 * g_globals_character) * 0x437C
                        + (3 * state->rows.selection + 30 * g_globals_difficulty) * 8 + 0x1E;
                    strcpy(slot, state->name);
                    strcpy(g_score->last_name, state->name);
                    reinterpret_cast<SubAnimNode&>(state->background).SetFlag();
                    state->state = SUBMENU_SAVE_CHOICE;
                    state->rows.item_count = 3;
                    state->rows.wrap = 1;
                    SelectInList(&state->rows, 0);
                    state->background.StopAtFrame3();
                    state->background.SetStopFrame((short)(state->rows.selection + 7));
                }
                g_sound_manager.Queue(SFX_CONFIRM, 0);
                goto cancel_check;
            }
            reinterpret_cast<SubAnimNode&>(state->background).SetFlag();
            state->state = SUBMENU_SAVE_CHOICE;
            state->rows.item_count = 3;
            state->rows.wrap = 1;
            SelectInList(&state->rows, 0);
            state->background.StopAtFrame3();
            state->background.SetStopFrame((short)(state->rows.selection + 7));
        }
        cancel_check:
        if (g_input_keys_held & KEY_CANCEL) {
            if (state->rows.selection >= 0) {
                if (state->name_length == 0)
                    return;
                g_sound_manager.Queue(SFX_CANCEL, 0);
                --state->name_length;
                state->name[state->name_length] = ' ';
                return;
            }
            state->state = SUBMENU_SAVE_CHOICE;
            state->rows.item_count = 3;
            SelectInList(&state->rows, 0);
            state->timer.SetSchedulerValue(0);
            g_sound_manager.Queue(SFX_CONFIRM, 0);
        }
        return;
    }
    case SUBMENU_FINAL_EXIT:
        // The final choice: 0 launches the next scene, 1/2 set the input mode.
        if (state->timer.field_04 < 12) break;
        reinterpret_cast<SubTimedState*>(state)->InitializeTimedState();
        state->state = SUBMENU_CLOSED;
        switch (state->rows.selection) {
        case 0:
            g_main_state = state->extra_cleared != 0 ? 10 : 13;
            return;
        case 1:
            SubSetInputMode(&g_application, 4);
            return;
        case 2:
            SubSetInputMode(&g_application, 4);
            return;
        }
        return;
    }
}
#pragma code_seg()
