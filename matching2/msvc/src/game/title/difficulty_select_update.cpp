// 0x00430320..0x00430697: difficulty selection screen of the title menu (and
// its five-entry phase table).
//
// Phase 0 creates the backdrop when it is not there yet, offers the four
// difficulties (or the single entry of a fixed-difficulty mode), installs and
// starts the selection animation and runs phase 1 on the same frame.  Phase 1
// waits seven frames.  Phase 2 moves the cursor and handles cancel and
// confirm.  Phase 3 leaves for the character selection after fourteen frames,
// phase 4 goes back to the main menu after six.
//
// The room is a stack argument here (the title dispatcher 0x0042CDF0 calls
// with the room pushed); the handler needs the dispatcher and the real bodies
// of its leaves in one whole-program link
// (build_support/layout/ltcg/difficulty_select_update.json).
//
// Shapes that are load-bearing (each measured against the image):
//
//  * The frame parameter of the slot-frame setter 0x0042C770 is a signed
//    short: `(short)selection + 7` is then loaded with `movsx`, while the
//    plain `selection + 0x11` of phase 0 keeps `xor; mov si`.
//  * 0x0042C750 is a member of the slot owner (slot loaded before the owner).
//  * The confirmed child is searched and stopped inside an inlined helper,
//    once per branch.  Inside the helper each search sits in a block of half
//    the entry weight, which lets the search with the constant script id of
//    the fixed entry inline while the computed id of the difficulty entries
//    stays a call; written in the handler itself neither inlines.  Each
//    branch stops its own named child, so the handle address is computed in
//    both and merged ahead of the frame constant (`lea eax,[child]; mov
//    esi,2`).  One call after the branches loads the constant first, and a
//    call on the returned temporary reuses the pointer the search returns.
//  * The backdrop resource is a named local and the handle a function-scope
//    local (one `push ecx` frame).
#include "th10/game/difficulty_select_update.hpp"

// Stop the child animation of the confirmed entry at frame 2.
static __forceinline void StopConfirmedChild(Title* room, int slot) {
    if (g_globals_difficulty < 4) {
        AnimationRef2 child =
            reinterpret_cast<AnimationHandle15*>(&room->animation_slots[slot])
                ->FindChildRef(room->cursor.selection + 0x6d);
        reinterpret_cast<AnimationHandle11*>(&child)->SetStopFrame(2);
    } else {
        AnimationRef2 child =
            reinterpret_cast<AnimationHandle15*>(&room->animation_slots[slot])
                ->FindChildRef(0x71);
        reinterpret_cast<AnimationHandle11*>(&child)->SetStopFrame(2);
    }
}

enum DifficultySelectPhase {
    DIFF_PHASE_ENTER = 0,
    DIFF_PHASE_WAIT_OPEN = 1,
    DIFF_PHASE_ACTIVE = 2,
    DIFF_PHASE_CONFIRM_LEAVE = 3,
    DIFF_PHASE_CANCEL_LEAVE = 4
};

enum DifficultySelectConstants {
    DIFF_LEVEL_EXTRA = 4,
    DIFF_KEY_CANCEL = 0x000A,
    DIFF_KEY_UP = 0x0010,
    DIFF_KEY_DOWN = 0x0020,
    DIFF_KEY_CONFIRM = 0x1001,
    DIFF_SFX_CONFIRM = 10,
    DIFF_SFX_CANCEL = 11,
    DIFF_SFX_MOVE = 12,
    DIFF_TARGET_MAIN_MENU = 2,
    DIFF_TARGET_CHARACTER = 7
};

#pragma code_seg(".text$00430320_fn")
__declspec(noinline) int __stdcall TitleMode6(Title* room) {
    int slot = (g_globals_difficulty >= DIFF_LEVEL_EXTRA) + 0x77;
    void* handle;
    switch (room->phase) {
    case DIFF_PHASE_ENTER:
        EnsureTitleMenuBackdrop(room, handle);
        room->cursor.item_count = g_globals_difficulty < DIFF_LEVEL_EXTRA ? 4 : 1;
        room->ClearAnimationSlot(slot);
        RecoveryMusicInstallSlot(room, slot);
        AnimationManager_SetStopFrameAndRun(
            3, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
            room->animation_slots[slot]);
        room->SetSlotFrame(slot, room->cursor.selection + 0x11);
        RecoveryMusicInstallSlot(room, 98);
        room->SetTimerTarget(DIFF_PHASE_WAIT_OPEN);
    case DIFF_PHASE_WAIT_OPEN:
        if (room->timer.current > 6)
            room->SetTimerTarget(DIFF_PHASE_ACTIVE);
        break;
    case DIFF_PHASE_ACTIVE:
        if (g_globals_difficulty < DIFF_LEVEL_EXTRA) {
            MenuCursor* cursor = &room->cursor;
            cursor->previous_selection = cursor->selection;
            if ((short)g_input_keys_raw.InputMaskActive(DIFF_KEY_UP)) cursor->Advance(-1);
            if ((short)g_input_keys_raw.InputMaskActive(DIFF_KEY_DOWN)) cursor->Advance(1);
            if (cursor->previous_selection != cursor->selection) {
                g_sound_manager.Queue(DIFF_SFX_MOVE, 0);
                reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(slot);
                room->SetSlotFrame(slot, (short)cursor->selection + 7);
            }
        }
        if (g_input_keys_held & DIFF_KEY_CANCEL) {
            room->SetTimerTarget(DIFF_PHASE_CANCEL_LEAVE);
            g_sound_manager.Queue(DIFF_SFX_CANCEL, 0);
            room->ClearAnimationSlot(slot);
        } else if (g_input_keys_held & DIFF_KEY_CONFIRM) {
            room->SetSlotFrame(slot, 6);
            StopConfirmedChild(room, slot);
            room->SetTimerTarget(DIFF_PHASE_CONFIRM_LEAVE);
            g_sound_manager.Queue(DIFF_SFX_CONFIRM, 0);
        }
        break;
    case DIFF_PHASE_CONFIRM_LEAVE:
        if (room->timer.current >= 14) {
            room->ClearAnimationSlot(98);
            room->DisableTimerWithOwner(DIFF_TARGET_CHARACTER);
            if (g_globals_difficulty < DIFF_LEVEL_EXTRA)
                g_globals_difficulty = room->cursor.selection;
            room->cursor.PushSelection();
            room->cursor.item_count = 2;
            UpdateBoundedCounter(g_globals_character, reinterpret_cast<unsigned int*>(&room->cursor));
        }
        break;
    case DIFF_PHASE_CANCEL_LEAVE:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(98);
            room->SetSlotFrame(0x5a, 8);
            room->SetSlotFrame(0x5b, 8);
            room->ClearAnimationSlot(94);
            RecoveryMusicStopHandle(&room->fallback_handle);
            room->DisableTimerWithOwner(DIFF_TARGET_MAIN_MENU);
            if (g_globals_difficulty < DIFF_LEVEL_EXTRA)
                g_globals_difficulty = room->cursor.selection;
            else
                g_globals_difficulty = reinterpret_cast<TitleDifficultyView*>(room)->saved_difficulty;
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}
#pragma code_seg()
