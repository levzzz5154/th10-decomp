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
#include "th10/game/key_config_update.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem5(MenuCursor& cursor, int index) {
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
static __forceinline void RunCursorSlot3(Title* room) {
    AnimationManager_SetStopFrameAndRun(3, reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl),
        room->animation_slots[2]);
}

enum KeyConfigPhase {
    KEYCFG_PHASE_ENTER = 0,
    KEYCFG_PHASE_WAIT_OPEN = 1,
    KEYCFG_PHASE_ACTIVE = 2,
    KEYCFG_PHASE_EXIT = 4
};

enum KeyConfigConstants {
    KEYCFG_ITEM_COUNT = 7,
    KEYCFG_LAST_BINDING_SLOT = 4,
    KEYCFG_ITEM_DEFAULTS = 5,
    KEYCFG_ITEM_QUIT = 6,
    KEYCFG_KEY_CANCEL = 0x000A,
    KEYCFG_KEY_UP = 0x0010,
    KEYCFG_KEY_DOWN = 0x0020,
    KEYCFG_KEY_CONFIRM = 0x1001,
    KEYCFG_SFX_CONFIRM = 10,
    KEYCFG_SFX_CANCEL = 11,
    KEYCFG_SFX_MOVE = 12,
    KEYCFG_TARGET_OPTIONS = 4
};

// Phase 2: cursor movement, pad button assignment, cancel and confirm.
static __forceinline void HandleInput(Title* room) {
    MenuCursor* cursor = &room->cursor;
    cursor->previous_selection = cursor->selection;
    if (g_input_keys_raw.Active(KEYCFG_KEY_UP))
        cursor->Advance(-1);
    if (g_input_keys_raw.Active(KEYCFG_KEY_DOWN))
        cursor->Advance(1);
    if (cursor->previous_selection != cursor->selection) {
        g_sound_manager.Queue(KEYCFG_SFX_MOVE, 0);
        RunCursorSlot3(room);
        room->SetSlotFrame(2, cursor->selection + 7);
    }

    unsigned char* buttons = Input_PollJoystickButtons2(0);
    for (int button = 0; button < 31; button++) {
        if (buttons[button] & 0x80) {
            if (cursor->selection <= KEYCFG_LAST_BINDING_SLOT)
                KeyConfigReassignSlot2(
                    reinterpret_cast<TitleKeyConfigView*>(room), cursor->selection, button);
            break;
        }
    }

    if ((g_input_keys_raw.pressed & KEYCFG_KEY_CANCEL) && cursor->selection == KEYCFG_ITEM_QUIT) {
        LoadBindings(room);
    } else {
        if ((g_input_keys_held & KEYCFG_KEY_CONFIRM) == 0)
            return;
        switch (cursor->selection) {
        case KEYCFG_ITEM_DEFAULTS:
            LoadBindings(room);
            g_sound_manager.Queue(KEYCFG_SFX_CONFIRM, 0);
            return;
        case KEYCFG_ITEM_QUIT: {
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
    g_sound_manager.Queue(KEYCFG_SFX_CANCEL, 0);
    room->SetSlotFrame(2, 6);
    room->SetTimerTarget(KEYCFG_PHASE_EXIT);
}

#pragma code_seg(".text$0042f540_fn")
int __stdcall TitleMenuFlow(Title* room) {
    switch (room->phase) {
    case KEYCFG_PHASE_ENTER:
        room->cursor.item_count = KEYCFG_ITEM_COUNT;
        SelectItem5(room->cursor, 0);
        RecoveryMusicInstallSlot(room, 2);
        room->SetTimerTarget(KEYCFG_PHASE_WAIT_OPEN);
        LoadBindings(room);
        // Retail intentionally processes phase 1 on this same frame.
    case KEYCFG_PHASE_WAIT_OPEN:
        if (room->timer.current > 6) {
            room->SetTimerTarget(KEYCFG_PHASE_ACTIVE);
            RunCursorSlot3(room);
            room->SetSlotFrame(2, room->cursor.selection + 17);
        }
        break;
    case KEYCFG_PHASE_ACTIVE:
        HandleInput(room);
        break;
    case KEYCFG_PHASE_EXIT:
        if (room->timer.current >= 10) {
            room->DisableTimerWithOwner(KEYCFG_TARGET_OPTIONS);
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}

#pragma code_seg()
