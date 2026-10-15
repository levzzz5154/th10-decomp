// 0x0042F540..0x0042F8AF: key configuration screen of the title menu (and its
// five-entry phase table).
//
// Phase 0 offers seven items, installs the screen's animation slot, copies
// the bindings in use into the screen and draws their labels, then runs
// phase 1 on the same frame.  Phase 1 waits seven frames and starts the
// cursor animation.  Phase 2 moves the cursor, assigns the first pad button
// that is down to the selected binding, and handles cancel and confirm: on
// "default" (item 5) the edited bindings are thrown away, on "quit" (item 6)
// they are stored in the configuration, and cancel on "quit" throws them away
// and leaves.  Phase 4 closes the screen after ten frames.
//
// The room arrives in EBX from the title dispatcher (0x0042CDF0); that private
// convention needs the dispatcher and the real bodies of the leaves in one
// whole-program link (build_support/layout/ltcg/key_config_update.json).
//
// Shapes that are load-bearing (each measured against the image):
//
//  * The configuration, its copy in the application state and the key state
//    are objects whose address is taken elsewhere, so every binding is stored
//    before the next one is loaded.  Declared as lone words the loads are
//    grouped ahead of the stores.
//  * Every path leaves through the one `return 1`.  With a `return` inside a
//    phase the compiler saves ESI at entry instead of after the phase check.
//  * The cancel test reads the pressed keys through the key state object and
//    the confirm test reads the lone word declared by the ending screen
//    header.  Read through one declaration the two tests share a register
//    copy (`mov eax,[pressed]; test al,0xa ... test eax,0x1001`), which is
//    what retail does only when no cursor test sits between them (0x00430320).
//  * The slot id is passed to the animation manager straight from the slot
//    array; copied into a local first the id and the manager load swap
//    registers.
#include "th10/game/key_config_update_0042f540.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem_0042f540(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = 0;
}

// Copy the bindings in use into the screen and redraw their labels.
static __forceinline void LoadBindings(Title* room) {
    TitleKeyConfigView* labels = reinterpret_cast<TitleKeyConfigView*>(room);
    labels->bindings_59cc[0] = g_key_bindings_current.keys[0];
    labels->bindings_59cc[1] = g_key_bindings_current.keys[1];
    labels->bindings_59cc[2] = g_key_bindings_current.keys[2];
    labels->bindings_59cc[3] = g_key_bindings_current.keys[3];
    labels->bindings_59cc[4] = g_key_bindings_current.skip;
    RefreshTitleKeyConfigView(labels);
}

// Restart the cursor animation of slot 2.
static __forceinline void RunCursorSlot_0042f540(Title* room) {
    AnimationManager_SetStopFrameAndRun(3, reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl),
        *reinterpret_cast<AnimationScriptId*>(&room->animation_slots[2]));
}

// Phase 2: cursor movement, pad button assignment, cancel and confirm.
static __forceinline void HandleInput(Title* room) {
    MenuCursor* cursor = &room->cursor;
    cursor->previous_selection = cursor->selection;
    if (g_input_keys_raw.Active(0x10))
        cursor->Advance(-1);
    if (g_input_keys_raw.Active(0x20))
        cursor->Advance(1);
    if (cursor->previous_selection != cursor->selection) {
        g_sound_manager.Queue(12, 0);
        RunCursorSlot_0042f540(room);
        room->SetSlotFrame(2, cursor->selection + 7);
    }

    unsigned char* buttons = Input_PollJoystickButtons_0044a4e0(0);
    for (int button = 0; button < 31; button++) {
        if (buttons[button] & 0x80) {
            if (cursor->selection <= 4)
                KeyConfigReassignSlot_00430250(
                    reinterpret_cast<TitleKeyConfigView*>(room), cursor->selection, button);
            break;
        }
    }

    if ((g_input_keys_raw.pressed & 0xa) && cursor->selection == 6) {
        LoadBindings(room);
    } else {
        if ((g_input_keys_held & 0x1001) == 0)
            return;
        switch (cursor->selection) {
        case 5:
            LoadBindings(room);
            g_sound_manager.Queue(10, 0);
            return;
        case 6: {
            TitleKeyConfigView* labels = reinterpret_cast<TitleKeyConfigView*>(room);
            g_key_bindings_current.keys[0] = labels->bindings_59cc[0];
            g_key_bindings_current.keys[1] = labels->bindings_59cc[1];
            g_key_bindings_current.keys[2] = labels->bindings_59cc[2];
            g_key_bindings_current.keys[3] = labels->bindings_59cc[3];
            g_key_bindings_current.skip = labels->bindings_59cc[4];
            g_key_bindings = g_key_bindings_current;
            break;
        }
        default:
            return;
        }
    }
    g_sound_manager.Queue(11, 0);
    room->SetSlotFrame(2, 6);
    room->SetTimerTarget(4);
}

#pragma code_seg(".text$0042f540_fn")
int __stdcall TitleMenuFlow(Title* room) {
    switch (room->phase) {
    case 0:
        room->cursor.item_count = 7;
        SelectItem_0042f540(room->cursor, 0);
        RecoveryMusicInstallSlot(room, 2);
        room->SetTimerTarget(1);
        LoadBindings(room);
        // Retail intentionally processes phase 1 on this same frame.
    case 1:
        if (room->timer.current > 6) {
            room->SetTimerTarget(2);
            RunCursorSlot_0042f540(room);
            room->SetSlotFrame(2, room->cursor.selection + 17);
        }
        break;
    case 2:
        HandleInput(room);
        break;
    case 4:
        if (room->timer.current >= 10) {
            room->DisableTimerWithOwner(4);
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}

#pragma code_seg()
