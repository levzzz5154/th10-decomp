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
// whole-program link (build_support/layout/ltcg/ending_screen_0042d300.json).
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
#include "th10/game/ending_screen_0042d300.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem_0042d300(MenuCursor& cursor, int selected) {
    if (cursor.item_count != 0)
        cursor.selection = selected >= cursor.item_count ? cursor.item_count - 1 : selected;
    else
        cursor.selection = selected;
}

#pragma code_seg(".text$0042d300_fn")
int __stdcall EndingScreen_Update_0042d300(Title* room) {
    switch (room->phase) {
    case 0: {
        if (reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(
                reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
                *reinterpret_cast<RecoveryScriptId*>(&room->animation_slots[88])) == 0) {
            RecoveryMusicInstallSlot(room, 88);
            RecoveryMusicInstallSlot(room, 90);
            void* handle;
            void** result = AnimationManager_CreatePrimaryBack(
                reinterpret_cast<void*>(room->reserved_018), &handle, 0, 15);
            room->reserved_684 = reinterpret_cast<unsigned int>(*result);
        }
        room->SetTimerTarget(1);
        SelectItem_0042d300(room->cursor, 0);
        // Retail intentionally processes phase 1 on this same frame.
    }
    case 1:
        if (room->timer.current > 10)
            room->SetTimerTarget(2);
        break;
    case 2:
        if ((g_input_keys_held & 0x160b) != 0) {
            room->SetSlotFrame(90, 6);
            room->SetTimerTarget(4);
            g_sound_manager.Queue(32, 0);
            RecoveryMusicStopHandle(
                reinterpret_cast<RecoveryHandle*>(&room->reserved_684));
        }
        break;
    case 4:
        if (room->timer.current >= 30)
            room->DisableTimerWithOwner(2);
        break;
    }
    return 1;
}

#pragma code_seg()
