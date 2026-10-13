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
#include "th10/game/replay_submenu_004236f0/state.hpp"

// The repeat-state twin the row screens poll: the 0x474E36 word first, then
// the pressed-edge byte at 0x474E34.
__forceinline short ChoiceInputActive(const KeyRepeatState* input, unsigned short mask) {
    if ((input->unknown_06 & mask) != 0) return 1;
    if ((input->pressed & mask) != 0) return 1;
    return 0;
}

// Select an item, keeping the selection inside a non-empty list.
__forceinline void SelectInList(SubmenuCursor_004236f0* cursor, int item) {
    if (cursor->item_count != 0)
        cursor->selection = item >= cursor->item_count ? cursor->item_count - 1 : item;
    else
        cursor->selection = item;
}

#pragma code_seg(".text$02h")
extern "C" __declspec(noinline) void __stdcall SubmenuUpdate_004236f0(SubmenuState_004236f0* state) {
    char path[64];
    switch (state->state) {
    case 6:
        // The confirm gate: after ten ticks, sound 10 and start the setup.
        if (state->timer.field_04 < 10) break;
        if ((data_00474e36 & 0x1001) == 0) break;
        data_00492590.Queue(10, 0);
        state->state = 7;
        state->background.SetStopFrame(2);
        state->timer.SetSchedulerValue(0);
        return;
    case 7:
        if (state->timer.field_04 < 10) break;
        SubUpdateFrameMaximum_004236f0(data_0047770c);
        if ((data_00474ca0 & 0x10) != 0) {
            // Ranking gate: publish the frame-maximum high score into the
            // stage/mode/subslot/difficulty slot of the score file.
            int* slot = reinterpret_cast<int*>(reinterpret_cast<char*>(data_0047783c)
                + (data_00474c6c + 3 * data_00474c68) * 0x437C
                + (data_00474c7c + 6 * data_00474c74) * 8 + 0x4DC);
            if (data_00474c44.score > *slot)
                *slot = data_00474c44.score;
            state->state = 8;
            state->rows.item_count = 3;
            state->rows.wrap = 1;
            SelectInList(&state->rows, 2);
            state->background.StopAtFrame3();
            state->background.SetStopFrame((unsigned short)(state->rows.selection + 7));
            return;
        }
        PrepareNameEntry_00423570(reinterpret_cast<NameEntryMenu_00423570*>(state));
        state->timer.SetSchedulerValue(0);
        if (state->no_entry == 0) {
            state->state = 12;
            reinterpret_cast<SubAnimNode_004236f0&>(state->background).ClearFlag();
            return;
        }
        state->state = 8;
        state->rows.item_count = 3;
        state->rows.wrap = 1;
        SelectInList(&state->rows, 2);
        state->background.StopAtFrame3();
        state->background.SetStopFrame((unsigned short)(state->rows.selection + 7));
        return;
    case 8: {
        // The save choice: navigate, confirm into the replay browser or the
        // alternate flow, cancel back to the three rows.
        SubmenuCursor_004236f0* rows = &state->rows;
        rows->previous_selection = rows->selection;
        if (ChoiceInputActive(&data_00474e30, 0x10))
            rows->Advance(-1);
        if (ChoiceInputActive(&data_00474e30, 0x20))
            rows->Advance(1);
        if (rows->previous_selection != rows->selection) {
            state->background.SetStopFrame((unsigned short)rows->selection + 7);
            data_00492590.Queue(12, 0);
        }
        if (data_00474e36 & 0x1001) {
            state->background.FindChildRef(rows->selection + 0x7C).StopAtFrame6();
            data_00492590.Queue(10, 0);
            state->state = 13;
            state->timer.SetSchedulerValue(0);
            SubUpdateFrameMaximum_004236f0(data_0047770c);
            switch (rows->selection) {
            case 1:
                state->timer.SetSchedulerValue(0);
                state->state = 10;
                reinterpret_cast<SubAnimNode_004236f0&>(state->background).ClearFlag();
                rows->PushSelection();
                state->rows.item_count = 25;
                state->rows.wrap = 1;
                SelectInList(rows, 0);
                for (int slot = 1; slot <= 25; ++slot) {
                    asm_sprintf_00452ae8(path, "th10_%.2d.rpy", slot);
                    state->handles[slot - 1] = ReplayManager_Create_004296f0(path);
                }
            break;
            case 2:
                state->timer.SetSchedulerValue(0);
                state->state = 13;
                data_00492590.Queue(10, 0);
                break;
            }
        }
        if (data_00474e36 & 0xA) {
            data_00492590.Queue(11, 0);
            if (rows->selection != 2) {
                SelectInList(rows, 2);
                state->background.SetStopFrame((short)rows->selection + 7);
            }
        }
        return;
    }
    case 10:
        // Replay-row browsing over the rows cursor; confirming hands the
        // shared list cursor over to the keyboard editor.
        if (state->timer.field_04 < 10) break;
        {
        SubmenuCursor_004236f0* rows = &state->rows;
        rows->previous_selection = rows->selection;
        if ((short)data_00474e30.InputMaskActive(0x10))
            rows->Advance(-1);
        if ((short)data_00474e30.InputMaskActive(0x20))
            rows->Advance(1);
        if (rows->previous_selection != rows->selection)
            data_00492590.Queue(12, 0);
        if (data_00474e36 & 0x1001) {
            state->state = 11;
            state->timer.SetSchedulerValue(0);
            SubmenuCursor_004236f0* list = &state->list;
            SelectInList(list, 0);
            state->list.item_count = (int)strlen(data_004746d8);
            state->list.wrap = 1;
            ReplayHeaderView_004236f0*& summary =
                reinterpret_cast<ReplayHeaderView_004236f0*&>(data_00477838->summary);
            if (state->extra_cleared != 0 && (data_00474ca0 & 0x10) == 0) {
                asm_FID_conflict___time32_00452b71(&summary->saved_time);
                summary->difficulty_slot = 8;
            } else {
                asm_FID_conflict___time32_00452b71(&summary->saved_time);
                summary->difficulty_slot = data_00474c7c;
            }
            strcpy(state->name, data_0047783c->last_name);
            state->name_length = 0;
            if (strcmp(state->name, "        ") != 0)
                list->Advance(-1);
            int length = 8;
            do {
                if (state->name[length - 1] != ' ')
                    goto timed_length;
                --length;
            } while (length > 0);
timed_length:
            state->name_length = length;
            data_00492590.Queue(10, 0);
            return;
        }
        if (data_00474e36 & 0xA) {
            // Cancel: release the 25 replay managers and restore the rows.
            state->state = 8;
            state->timer.SetSchedulerValue(0);
            reinterpret_cast<SubAnimNode_004236f0&>(state->background).SetFlag();
            state->rows.PopSelection();
            state->rows.item_count = 3;
            state->rows.wrap = 1;
            state->background.SetStopFrame((short)state->rows.selection + 7);
            for (int index = 0; index < 25; ++index) {
                void* handle = state->handles[index];
                if (handle) {
                    ReplayManager_Destroy_004294a0(handle);
                    asm_free_004524a1(handle);
                }
                state->handles[index] = 0;
            }
            state->state = 8;
            state->timer.SetSchedulerValue(0);
            data_00492590.Queue(11, 0);
        }
        return;
    }
    case 11: {
        // The 13-column keyboard editor: letters, space, backspace, save.
        if (state->timer.field_04 < 10) break;
        SubmenuCursor_004236f0* list = &state->list;
        list->previous_selection = list->selection;
        if ((short)data_00474e30.InputMaskActive(0x10))
            list->Advance(-13);
        if ((short)data_00474e30.InputMaskActive(0x20))
            list->Advance(13);
        if ((short)data_00474e30.InputMaskActive(0x40)) {
            if (list->selection % 13)
                list->Advance(-1);
            else
                list->Advance(12);
        }
        if ((short)data_00474e30.InputMaskActive(0x80)) {
            if (list->selection % 13 == 12)
                list->Advance(-12);
            else
                list->Advance(1);
        }
        if (list->previous_selection != list->selection)
            data_00492590.Queue(12, 0);
        if (data_00474e36 & 0x1001) {
            const char* grid = data_004746d8;
            int selection = list->selection;
            int length = (int)strlen(grid);
            if (selection < length - 3) {
                if (state->name_length < 8)
                    state->name[state->name_length] = grid[selection];
                else
                    state->name[state->name_length - 1] = grid[selection];
            } else if (selection == length - 3) {
                if (state->name_length < 8)
                    state->name[state->name_length] = ' ';
                else
                    state->name[state->name_length - 1] = ' ';
            } else if (selection == length - 2) {
                if (state->name_length == 0)
                    return;
                --state->name_length;
                state->name[state->name_length] = ' ';
                data_00492590.Queue(11, 0);
                return;
            } else if (selection == length - 1) {
                // The save column: serialize the replay under the typed name.
                data_00492590.Queue(44, 0);
                asm_sprintf_00452ae8(path, "th10_%.2d.rpy", selection + 1);
                SubPlatformResource_Destroy_004236f0(
                    reinterpret_cast<PlatformResource*>(state->handles[selection]));
                asm_FUN_00429b60_00429b60(data_00477838, path, state->name);
                state->handles[selection] =
                    ReplayManager_Create_004296f0(path);
                state->state = 10;
                state->timer.SetSchedulerValue(0);
                strcpy(data_0047783c->last_name, state->name);
                return;
            }
            // The letter/space cells share the length bump and the append
            // sound, then fall through to the cancel test in the same frame.
            ++state->name_length;
            if (state->name_length >= 8)
                UpdateBoundedCounter(length - 1, (unsigned int*)&list->selection);
            data_00492590.Queue(10, 0);
        }
        if (data_00474e36 & 0xA) {
            data_00492590.Queue(11, 0);
            if (state->name_length != 0) {
                --state->name_length;
                state->name[state->name_length] = ' ';
                return;
            }
            state->state = 10;
            state->timer.SetSchedulerValue(0);
        }
        return;
    }
    case 12: {
        // The alternate keyboard path; the no_entry latch swaps the editing
        // pass for the task re-registration.
        SubmenuCursor_004236f0* list = &state->list;
        if (state->no_entry == 0) {
            list->previous_selection = list->selection;
            if ((short)data_00474e30.InputMaskActive(0x10))
                list->Advance(-13);
            if ((short)data_00474e30.InputMaskActive(0x20))
                list->Advance(13);
            if ((short)data_00474e30.InputMaskActive(0x40)) {
                if (list->selection % 13)
                    list->Advance(-1);
                else
                    list->Advance(12);
            }
            if ((short)data_00474e30.InputMaskActive(0x80)) {
                if (list->selection % 13 == 12)
                    list->Advance(-12);
                else
                    list->Advance(1);
            }
            if (list->previous_selection != list->selection)
                data_00492590.Queue(12, 0);
        }
        if (data_00474e36 & 0x1001) {
            if (state->no_entry == 0) {
                const char* grid = data_004746d8;
                int selection = list->selection;
                int length = (int)strlen(grid);
                if (selection < length - 3) {
                    if (state->name_length < 8) {
                        state->name[state->name_length] = grid[selection];
                        ++state->name_length;
                        if (state->name_length >= 8)
                            UpdateBoundedCounter(length - 1, (unsigned int*)&list->selection);
                    } else {
                        state->name[state->name_length - 1] = grid[selection];
                    }
                } else if (selection == length - 3) {
                    if (state->name_length < 8)
                        state->name[state->name_length] = ' ';
                    else
                        state->name[state->name_length - 1] = ' ';
                    ++state->name_length;
                    if (state->name_length >= 8)
                        UpdateBoundedCounter(length - 1, (unsigned int*)&list->selection);
                } else if (selection == length - 2) {
                    if (state->name_length == 0)
                        return;
                    --state->name_length;
                    state->name[state->name_length] = ' ';
                } else if (selection == length - 1) {
                    // Save the name into the stage/mode/subslot slot table.
                    char* slot = reinterpret_cast<char*>(data_0047783c)
                        + (data_00474c6c + 3 * data_00474c68) * 0x437C
                        + (3 * selection + 30 * data_00474c74) * 8 + 0x1E;
                    strcpy(slot, state->name);
                    strcpy(data_0047783c->last_name, state->name);
                    reinterpret_cast<SubAnimNode_004236f0&>(state->background).SetFlag();
                    state->state = 8;
                    state->rows.item_count = 3;
                    state->rows.wrap = 1;
                    SelectInList(&state->rows, 0);
                    state->background.StopAtFrame3();
                    state->background.SetStopFrame((short)(state->rows.selection + 7));
                }
                data_00492590.Queue(10, 0);
                goto cancel_check;
            }
            reinterpret_cast<SubAnimNode_004236f0&>(state->background).SetFlag();
            state->state = 8;
            state->rows.item_count = 3;
            state->rows.wrap = 1;
            SelectInList(&state->rows, 0);
            state->background.StopAtFrame3();
            state->background.SetStopFrame((short)(state->rows.selection + 7));
        }
        cancel_check:
        if (data_00474e36 & 0xA) {
            if (state->rows.selection >= 0) {
                if (state->name_length == 0)
                    return;
                data_00492590.Queue(11, 0);
                --state->name_length;
                state->name[state->name_length] = ' ';
                return;
            }
            state->state = 8;
            state->rows.item_count = 3;
            SelectInList(&state->rows, 0);
            state->timer.SetSchedulerValue(0);
            data_00492590.Queue(10, 0);
        }
        return;
    }
    case 13:
        // The final choice: 0 launches the next scene, 1/2 set the input mode.
        if (state->timer.field_04 < 12) break;
        reinterpret_cast<SubTimedState_004236f0*>(state)->InitializeTimedState();
        state->state = 21;
        switch (state->rows.selection) {
        case 0:
            data_00491fb8 = state->extra_cleared != 0 ? 10 : 13;
            return;
        case 1:
        case 2:
            SubSetInputMode_004236f0(&data_00491c28, 4);
            return;
        }
        return;
    }
}
#pragma code_seg()

// The private-ABI dependency bodies, co-compiled into this cluster and
// anchored at their retail addresses.
#include "../../layout/ltcg/replay_submenu_004236f0/find.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/setstop.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/child.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/mark6.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/stop3.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/stop1.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/nodeflag.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/inputmode.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/timer.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/queue.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/cursor.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/frame.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/timed.cpp"
#include "../../layout/ltcg/replay_submenu_004236f0/destroy.cpp"
