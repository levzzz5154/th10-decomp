// 0x0042D300..0x0042D41F: ending screen phase handler (and its five-entry
// phase table).
//
// Phase 0 installs the two ending animation slots and the backdrop when they
// are not alive yet, starts the timer and selects the first item, then runs
// phase 1 on the same frame.  Phase 1 waits ten frames, phase 2 waits for a
// confirm/cancel input and starts the fade-out, phase 4 closes the screen
// after thirty frames.
//
// The room arrives in EBX from the title dispatcher (0x0042CDF0); that private
// convention needs the dispatcher and the real slot/timer leaves in one
// whole-program link (build_support/layout/ltcg/ending_screen.json).
//
// Two shapes are load-bearing (each measured against the image):
//
//  * The selection goes through the cursor's inlined select-and-clamp.  With
//    the three arms written out as separate zero stores the compiler keeps a
//    shared zero in ESI for the whole function.
//  * The slot id is passed to Find straight from the slot array as an id
//    object.  Copied into a local first, the argument is no longer an
//    expression temporary and the two later temporaries take EAX/ECX instead
//    of retail's ECX/EDX.
#include "th10/game/title_opening_screen.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem2(MenuCursor& cursor, int selected) {
    if (cursor.item_count != 0)
        cursor.selection = selected >= cursor.item_count ? cursor.item_count - 1 : selected;
    else
        cursor.selection = selected;
}

enum TitleOpeningPhase {
    OPENING_PHASE_ENTER = 0,
    OPENING_PHASE_WAIT_OPEN = 1,
    OPENING_PHASE_WAIT_KEY = 2,
    OPENING_PHASE_FADE_OUT = 4
};

enum TitleOpeningConstants {
    OPENING_ANY_KEY_MASK = 0x160B,
    OPENING_SFX_START = 32,
    OPENING_TARGET_MAIN_MENU = 2
};

#pragma code_seg(".text$0042d300_fn")
int __stdcall TitleOpening_Update(Title* room) {
    switch (room->phase) {
    case OPENING_PHASE_ENTER: {
        if (reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(
                reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl),
                room->animation_slots[88]) == 0) {
            Title_InstallAnimationSlot(room, 88);
            Title_InstallAnimationSlot(room, 90);
            void* handle;
            void** result = AnimationManager_CreatePrimaryBack(
                reinterpret_cast<void*>(room->reserved_018), &handle, 0, 15);
            room->reserved_684 = reinterpret_cast<unsigned int>(*result);
        }
        room->SetPhase(OPENING_PHASE_WAIT_OPEN);
        SelectItem2(room->cursor, 0);
        // Retail intentionally processes phase 1 on this same frame.
    }
    case OPENING_PHASE_WAIT_OPEN:
        if (room->timer.current > 10)
            room->SetPhase(OPENING_PHASE_WAIT_KEY);
        break;
    case OPENING_PHASE_WAIT_KEY:
        if ((g_input_keys_held & OPENING_ANY_KEY_MASK) != 0) {
            room->SetSlotFrame(90, 6);
            room->SetPhase(OPENING_PHASE_FADE_OUT);
            g_sound_manager.Queue(OPENING_SFX_START, 0);
            Title_StopAnimationHandle(
                reinterpret_cast<AnmScriptHandle*>(&room->reserved_684));
        }
        break;
    case OPENING_PHASE_FADE_OUT:
        if (room->timer.current >= 30)
            room->SetMode(OPENING_TARGET_MAIN_MENU);
        break;
    }
    return 1;
}

#pragma code_seg()
