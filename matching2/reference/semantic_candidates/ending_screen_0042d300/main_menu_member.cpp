// Complete readable main-menu state machine; unselected native candidate.
struct GameProgress_0042c850 {
    unsigned char reserved[0x1d888];
    unsigned char record_present[6];
    __declspec(noinline) int HasAnyPlayRecord();
};
extern "C" GameProgress_0042c850* data_0047783c;
extern "C" unsigned short data_00474e34;
struct AnimationLookupContext;
struct AnimationScriptId { int value; };
struct GameAnimationSlots;
__declspec(noinline) void __fastcall AnimationManager_SetStopFrameAndRun(
    unsigned short frame, AnimationLookupContext* manager, AnimationScriptId id);
__declspec(noinline) void __fastcall DispatchAnimationSlotSecondary(
    int slot, GameAnimationSlots* room);
__declspec(noinline) unsigned int __fastcall UpdateBoundedCounter(
    unsigned int requested, unsigned int* counter);
struct TitleDifficultyView {
    unsigned char reserved[0x58f0];
    int saved_difficulty;
};

static __forceinline void UpdateSelectionAnimation(RecoveryMusicRoom_00433ef0* room) {
    AnimationScriptId id = { static_cast<int>(room->animation_slots[0]) };
    AnimationManager_SetStopFrameAndRun(3, reinterpret_cast<AnimationLookupContext*>(data_00491c10), id);
    room->SetSlotFrame(0, static_cast<unsigned short>(room->cursor.selection + 17));
}

#pragma code_seg(".text$0042d420_fn")
int TitleRuntime::MainMenuUpdate() {
    RecoveryMusicRoom_00433ef0* room = this;
    switch (room->phase) {
    case 0: {
        room->cursor.item_count = 8;
        if (!data_0047783c->HasAnyPlayRecord()) {
            room->cursor.disabled_items[room->cursor.disabled_count] = 1;
            ++room->cursor.disabled_count;
        }
        if (data_00474ca0 & 0x10) {
            SetSelection(&room->cursor, 2);
            data_00474ca0 &= ~0x10u;
        }
        RecoveryScriptId_0040bd80 id = { static_cast<int>(room->animation_slots[88]) };
        if (!reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
                reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), id))
            RecoveryMusicInstallSlot_0042c670(room, 88);
        RecoveryMusicInstallSlot_0042c670(room, 0);
        room->SetTimerTarget(1);
    }
    case 1:
        if (room->timer.current > 10) {
            room->SetTimerTarget(2);
            UpdateSelectionAnimation(room);
        }
        break;
    case 2: {
        room->cursor.previous_selection = room->cursor.selection;
        if ((data_00474e36 & 0x10) || (data_00474e34 & 0x10))
            room->cursor.Advance(-1);
        if ((data_00474e36 & 0x20) || (data_00474e34 & 0x20))
            room->cursor.Advance(1);
        if (room->cursor.previous_selection != room->cursor.selection) {
            data_00492590.Queue(12, 0);
            UpdateSelectionAnimation(room);
        }
        bool exit_requested = false;
        if (data_00474e36 & 10) {
            if (room->cursor.selection == 7) {
                exit_requested = true;
            } else {
                data_00492590.Queue(11, 0);
                SetSelection(&room->cursor, 7);
                DispatchAnimationSlotSecondary(0, reinterpret_cast<GameAnimationSlots*>(room));
                room->SetSlotFrame(0, static_cast<unsigned short>(room->cursor.selection + 7));
            }
        }
        if (exit_requested) {
            data_00492590.Queue(11, 0);
            room->SetTimerTarget(4);
            return 1;
        }
        if (data_00474e36 & 0x1001) {
            room->SetSlotFrame(0, 6);
            switch (room->cursor.selection) {
            case 0: case 1: case 2: case 3: case 4:
                data_00492590.Queue(10, 0);
                room->SetSlotFrame(90, 7);
                room->SetSlotFrame(91, 7);
                room->SetTimerTarget(4);
                return 1;
            case 5:
                data_00492590.Queue(10, 0);
                room->SetSlotFrame(90, 7);
                room->SetSlotFrame(91, 7);
                room->SetTimerTarget(4);
                data_00492590.Queue(10, 0);
                return 1;
            case 6:
                data_00492590.Queue(10, 0);
                room->SetTimerTarget(4);
                DispatchAnimationSlotSecondary(90, reinterpret_cast<GameAnimationSlots*>(room));
                DispatchAnimationSlotSecondary(91, reinterpret_cast<GameAnimationSlots*>(room));
                return 1;
            case 7:
                data_00492590.Queue(11, 0);
                room->SetTimerTarget(4);
                return 1;
            }
        }
        break;
    }
    case 4:
        if (room->timer.current < 20)
            break;
        switch (room->cursor.selection) {
        case 0: case 2:
            if (room->cursor.selection == 0)
                data_00474ca0 &= ~0x10u;
            else
                data_00474ca0 |= 0x10;
            room->ClearAnimationSlot(88);
            room->DisableTimerWithOwner(6);
            room->cursor.PushSelection();
            if (data_00474c74 > 3)
                data_00474c74 = 1;
            UpdateBoundedCounter(data_00474c74,
                reinterpret_cast<unsigned int*>(&room->cursor.selection));
            return 1;
        case 1:
            data_00474ca0 &= ~0x10u;
            room->ClearAnimationSlot(88);
            room->DisableTimerWithOwner(6);
            room->cursor.PushSelection();
            reinterpret_cast<TitleDifficultyView*>(room)->saved_difficulty = data_00474c74;
            data_00474c74 = 4;
            SetSelection(&room->cursor, 0);
            return 1;
        case 3:
            room->ClearAnimationSlot(88);
            room->DisableTimerWithOwner(12);
            room->cursor.PushSelection();
            return 1;
        case 4:
            room->ClearAnimationSlot(88);
            room->DisableTimerWithOwner(11);
            room->cursor.PushSelection();
            return 1;
        case 5:
            room->ClearAnimationSlot(88);
            room->DisableTimerWithOwner(14);
            room->cursor.PushSelection();
            return 1;
        case 6:
            room->DisableTimerWithOwner(4);
            room->cursor.PushSelection();
            return 1;
        case 7:
            room->DisableTimerWithOwner(3);
            break;
        }
        break;
    }
    return 1;
}
#pragma code_seg()
