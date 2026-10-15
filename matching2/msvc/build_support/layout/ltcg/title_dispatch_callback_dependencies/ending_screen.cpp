// Readable baseline only: not selected for image reconstruction.
// Retail takes room in EBX; recovering that contract needs the full dispatcher.
#include "th10/game/title_menu.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" unsigned int data_00474e36;
__declspec(noinline) void __stdcall RecoveryMusicInstallSlot_0042c670(
    Title* room, int index);
struct AnimationHandle_0040c3c0 { unsigned int id; };
__declspec(noinline) void StopHandle_00409e50(AnimationHandle_0040c3c0* handle);

#pragma code_seg(".text$0042d300_fn")
__declspec(noinline) int __stdcall EndingScreen_Update_0042d300(
        Title* room) {
    switch (room->phase) {
    case 0: {
        RecoveryScriptId_0040bd80 id = { static_cast<int>(room->animation_slots[88]) };
        if (reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(
                reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl), id) == 0) {
            RecoveryMusicInstallSlot_0042c670(room, 88);
            RecoveryMusicInstallSlot_0042c670(room, 90);
            void* handle;
            void** result = AnimationManager_CreatePrimaryBack_00448d00(
                reinterpret_cast<void*>(room->reserved_018), &handle, 0, 15);
            room->reserved_684 = reinterpret_cast<unsigned int>(*result);
        }
        room->SetTimerTarget(1);
        int count = room->cursor.item_count;
        if (count == 0)
            room->cursor.selection = 0;
        else if (count < 1)
            room->cursor.selection = count - 1;
        else
            room->cursor.selection = 0;
        // Retail intentionally processes phase 1 on this same frame.
    }
    case 1:
        if (room->timer.current > 10)
            room->SetTimerTarget(2);
        break;
    case 2:
        if ((data_00474e36 & 0x160b) != 0) {
            room->SetSlotFrame(90, 6);
            room->SetTimerTarget(4);
            data_00492590.Queue(32, 0);
            StopHandle_00409e50(reinterpret_cast<AnimationHandle_0040c3c0*>(
                &room->reserved_684));
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
