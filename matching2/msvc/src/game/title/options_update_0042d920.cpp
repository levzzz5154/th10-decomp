// 0x0042D920..0x0042E593: options screen of the title menu (and its
// five-entry phase table).
//
// Phase 0 offers the six items (screen mode, music volume, sound volume, key
// configuration, defaults, quit) and runs phase 1 on the same frame.  Phase 1
// waits seven frames and shows the labels of the current screen mode.  Phase
// 2 moves the cursor; left and right change the item under it, confirm opens
// the key configuration, restores the defaults or leaves, cancel moves to
// "quit" (and leaves when the cursor is already there).  On the sound volume
// a test sound plays once a second.  Phase 4 opens the key configuration or
// goes back to the main menu after ten frames.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (layout/ltcg/difficulty_select_update_00430320.json).
#include "th10/game/options_update_0042d920.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem_0042d920(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// The child animation `script` of an animation slot (0x004497D0 with the
// manager already loaded).
static __forceinline AnimationRef_004497d0 FindChild_0042d920(
        RecoveryLookupContext_0040bd80* manager, RecoveryScriptId_0040bd80* slot, int script) {
    LabelParent_0042d920* parent = static_cast<LabelParent_0042d920*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(manager)->Find(manager, *slot));
    if (parent == 0)
        slot->value = 0;
    for (LabelLink_0042d920* link = &parent->children; link != 0; link = link->next)
        if (link->object->script == script)
            return AnimationRef_004497d0(link->object->id);
    return AnimationRef_004497d0(0);
}

// Show a sprite on the child animation `script` of the options slot.
static __forceinline void ShowLabel_0042d920(
        RecoveryLookupContext_0040bd80* manager, RecoveryMusicRoom_00433ef0* room, int script, int sprite) {
    AnimationRef_004497d0 child = FindChild_0042d920(
        manager, reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[1]), script);
    reinterpret_cast<SpriteHandle_00449670*>(&child)->SelectSprite(sprite);
}

// Show the two labels of the current screen mode.
static __forceinline void ShowModeLabels_0042d920(
        RecoveryLookupContext_0040bd80* manager, RecoveryMusicRoom_00433ef0* room) {
    if (data_00491d4c.screen_mode == 0) {
        ShowLabel_0042d920(manager, room, 0x1f, 0x2e);
        ShowLabel_0042d920(manager, room, 0x20, 0x2f);
    } else if (data_00491d4c.screen_mode == 1) {
        ShowLabel_0042d920(manager, room, 0x1f, 0x30);
        ShowLabel_0042d920(manager, room, 0x20, 0x31);
    } else {
        ShowLabel_0042d920(manager, room, 0x1f, 0x2c);
        ShowLabel_0042d920(manager, room, 0x20, 0x2d);
    }
}

static __forceinline void ShowScreenMode_0042d920(RecoveryMusicRoom_00433ef0* room) {
    RecoveryLookupContext_0040bd80* manager = reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10);
    ShowModeLabels_0042d920(manager, room);
}

// Restart the cursor animation of slot 1.
static __forceinline void RunCursorSlot_0042d920(RecoveryMusicRoom_00433ef0* room) {
    AnimationManager_SetStopFrameAndRun(
        3, reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10),
        *reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[1]));
}

#pragma code_seg(".text$0042d920_fn")
__declspec(noinline) int __stdcall TitleOptions_0042d920(RecoveryMusicRoom_00433ef0* room) {
    switch (room->phase) {
    case 0:
        room->cursor.item_count = 6;
        SelectItem_0042d920(room->cursor, 0);
        RecoveryMusicInstallSlot_0042c670(room, 1);
        RefreshOptions_0042e5a0(room);
        room->SetTimerTarget(1);
    case 1:
        if (room->timer.current > 6) {
            room->SetTimerTarget(2);
            RunCursorSlot_0042d920(room);
            ShowScreenMode_0042d920(room);
            room->SetSlotFrame(1, room->cursor.selection + 0x11);
        }
        break;
    case 2: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)data_00474e30.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)data_00474e30.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            application_state_00491c00.sound.Queue(12, 0);
            RunCursorSlot_0042d920(room);
            room->SetSlotFrame(1, room->cursor.selection + 7);
        }
        if (data_00474e36 & 8)
            goto cancel;
        if (data_00474e36 & 2) {
        cancel:
            if (room->cursor.selection == 5) {
                room->SetSlotFrame(1, 6);
                application_state_00491c00.sound.Queue(11, 0);
                room->SetTimerTarget(4);
            } else {
                application_state_00491c00.sound.Queue(11, 0);
                SelectItem_0042d920(room->cursor, 5);
                reinterpret_cast<AnimationSlotOwner_0042c750*>(room)->RestartSlot(1);
                room->SetSlotFrame(1, room->cursor.selection + 7);
            }
        } else {
            // The test sound of the sound volume item.
            if (room->cursor.selection == 2
                    && reinterpret_cast<FrameCounterPair*>(&room->timer)->AtInterval(60))
                application_state_00491c00.sound.Queue(4, 0);
            RecoveryLookupContext_0040bd80* manager;
            if ((short)data_00474e30.InputMaskActive(0x40)) {
                manager = reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10);
                switch (room->cursor.selection) {
                case 0:
                    if (data_00491d4c.screen_mode > 0)
                        --data_00491d4c.screen_mode;
                    else
                        data_00491d4c.screen_mode = 2;
                    ShowModeLabels_0042d920(manager, room);
                    application_state_00491c00.sound.Queue(12, 0);
                    break;
                case 1:
                    // Both paths converge on the label refresh; MSVC's LTCG tail-duplicates
                    // the call into each branch, which keeps the `mov edi,ebp` argument
                    // setup per-branch and the decrement a split `add al,0xfb` instead of
                    // the folded `add byte ptr [mem],0xfb` a shared call site would fold to.
                    if (data_00491d4c.music_volume < 5) {
                        data_00491d4c.music_volume = 0;
                        goto refresh_music;
                    }
                    data_00491d4c.music_volume += 0xFB;
                refresh_music:
                    RefreshOptions_0042e5a0(room);
                    break;
                case 2:
                    if (data_00491d4c.sound_volume < 5) {
                        data_00491d4c.sound_volume = 0;
                        goto refresh_sound;
                    }
                    data_00491d4c.sound_volume += 0xFB;
                refresh_sound:
                    RefreshOptions_0042e5a0(room);
                    break;
                }
            }
            else
                manager = reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10);
            if ((short)data_00474e30.InputMaskActive(0x80)) {
                switch (room->cursor.selection) {
                case 0:
                    if (data_00491d4c.screen_mode < 2)
                        ++data_00491d4c.screen_mode;
                    else
                        data_00491d4c.screen_mode = 0;
                    application_state_00491c00.sound.Queue(12, 0);
                    ShowModeLabels_0042d920(manager, room);
                    break;
                case 1:
                    data_00491d4c.music_volume += 5;
                    if (data_00491d4c.music_volume > 100)
                        data_00491d4c.music_volume = 100;
                    RefreshOptions_0042e5a0(room);
                    break;
                case 2:
                    data_00491d4c.sound_volume += 5;
                    if (data_00491d4c.sound_volume > 100)
                        data_00491d4c.sound_volume = 100;
                    RefreshOptions_0042e5a0(room);
                    break;
                }
            }
            if (data_00474e36 & 0x1001) {
                switch (room->cursor.selection) {
                case 5:
                    room->SetSlotFrame(1, 6);
                    application_state_00491c00.sound.Queue(11, 0);
                    room->SetTimerTarget(4);
                    break;
                case 4:
                    data_00491d4c.music_volume = 100;
                    data_00491d4c.sound_volume = 80;
                    data_00491d4c.screen_mode = 0;
                    RefreshOptions_0042e5a0(room);
                    ShowModeLabels_0042d920(manager, room);
                    application_state_00491c00.sound.Queue(10, 0);
                    break;
                case 3:
                    room->SetSlotFrame(1, 6);
                    application_state_00491c00.sound.Queue(10, 0);
                    room->SetTimerTarget(4);
                    break;
                }
            }
        }
        break;
    }
    case 4:
        if (room->timer.current >= 10) {
            MenuCursor* cursor = &room->cursor;
            switch (cursor->selection) {
            case 3:
                room->DisableTimerWithOwner(5);
                cursor->PushSelection();
                break;
            case 5:
                reinterpret_cast<AnimationSlotOwner_0042c750*>(room)->StopSlot(0x5a);
                reinterpret_cast<AnimationSlotOwner_0042c750*>(room)->StopSlot(0x5b);
                room->DisableTimerWithOwner(2);
                cursor->PopSelection();
                break;
            }
        }
        break;
    }
    return 1;
}
#pragma code_seg()
