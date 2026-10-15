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
// (build_support/layout/ltcg/difficulty_select_update_00430320.json).
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
#include "th10/game/difficulty_select_update_00430320.hpp"

// Stop the child animation of the confirmed entry at frame 2.
static __forceinline void StopConfirmedChild_00430320(Title* room, int slot) {
    if (g_globals_difficulty < 4) {
        AnimationRef_004497d0 child =
            reinterpret_cast<AnimationHandle_004497d0*>(&room->animation_slots[slot])
                ->FindChildRef(room->cursor.selection + 0x6d);
        reinterpret_cast<AnimationHandle_00449470*>(&child)->SetStopFrame(2);
    } else {
        AnimationRef_004497d0 child =
            reinterpret_cast<AnimationHandle_004497d0*>(&room->animation_slots[slot])
                ->FindChildRef(0x71);
        reinterpret_cast<AnimationHandle_00449470*>(&child)->SetStopFrame(2);
    }
}

#pragma code_seg(".text$00430320_fn")
__declspec(noinline) int __stdcall TitleMode6_00430320(Title* room) {
    int slot = (g_globals_difficulty >= 4) + 0x77;
    void* handle;
    switch (room->phase) {
    case 0:
        if (reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(
                reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId*>(&room->animation_slots[94])) == 0) {
            RecoveryMusicInstallSlot(room, 94);
            void* resource = g_ascii_manager->animation_resource;
            void** result = AnimationManager_CreatePrimaryBack_00448d00(resource, &handle, 8, 15);
            room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
        }
        room->cursor.item_count = g_globals_difficulty < 4 ? 4 : 1;
        room->ClearAnimationSlot(slot);
        RecoveryMusicInstallSlot(room, slot);
        AnimationManager_SetStopFrameAndRun(
            3, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
            *reinterpret_cast<RecoveryScriptId*>(&room->animation_slots[slot]));
        room->SetSlotFrame(slot, room->cursor.selection + 0x11);
        RecoveryMusicInstallSlot(room, 98);
        room->SetTimerTarget(1);
    case 1:
        if (room->timer.current > 6)
            room->SetTimerTarget(2);
        break;
    case 2:
        if (g_globals_difficulty < 4) {
            MenuCursor* cursor = &room->cursor;
            cursor->previous_selection = cursor->selection;
            if ((short)g_input_keys_raw.InputMaskActive(0x10)) cursor->Advance(-1);
            if ((short)g_input_keys_raw.InputMaskActive(0x20)) cursor->Advance(1);
            if (cursor->previous_selection != cursor->selection) {
                g_sound_manager.Queue(12, 0);
                reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(slot);
                room->SetSlotFrame(slot, (short)cursor->selection + 7);
            }
        }
        if (g_input_keys_held & 0xa) {
            room->SetTimerTarget(4);
            g_sound_manager.Queue(11, 0);
            room->ClearAnimationSlot(slot);
        } else if (g_input_keys_held & 0x1001) {
            room->SetSlotFrame(slot, 6);
            StopConfirmedChild_00430320(room, slot);
            room->SetTimerTarget(3);
            g_sound_manager.Queue(10, 0);
        }
        break;
    case 3:
        if (room->timer.current >= 14) {
            room->ClearAnimationSlot(98);
            room->DisableTimerWithOwner(7);
            if (g_globals_difficulty < 4)
                g_globals_difficulty = room->cursor.selection;
            room->cursor.PushSelection();
            room->cursor.item_count = 2;
            UpdateBoundedCounter(g_globals_character, reinterpret_cast<unsigned int*>(&room->cursor));
        }
        break;
    case 4:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(98);
            room->SetSlotFrame(0x5a, 8);
            room->SetSlotFrame(0x5b, 8);
            room->ClearAnimationSlot(94);
            RecoveryMusicStopHandle_00409e50(&room->fallback_handle);
            room->DisableTimerWithOwner(2);
            if (g_globals_difficulty < 4)
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
