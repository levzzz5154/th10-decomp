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
// (build_support/layout/ltcg/difficulty_select_update.json).
#include "th10/game/options_update.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem4(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// The child animation `script` of an animation slot (0x004497D0 with the
// manager already loaded).
static __forceinline AnimationRef2 FindChild2(
        AnmLookupContext* manager, AnimationScriptId* slot, int script) {
    LabelParent* parent = static_cast<LabelParent*>(
        reinterpret_cast<AnmLookup*>(manager)->Find(manager, *slot));
    if (parent == 0)
        slot->value = 0;
    for (LabelLink* link = &parent->children; link != 0; link = link->next)
        if (link->object->script == script)
            return AnimationRef2(link->object->id);
    return AnimationRef2(0);
}

// Show a sprite on the child animation `script` of the options slot.
static __forceinline void ShowLabel(
        AnmLookupContext* manager, Title* room, int script, int sprite) {
    AnimationRef2 child = FindChild2(
        manager, &room->animation_slots[1], script);
    reinterpret_cast<SpriteHandle*>(&child)->SelectSprite(sprite);
}

// Show the two labels of the current screen mode.
static __forceinline void ShowModeLabels(
        AnmLookupContext* manager, Title* room) {
    if (g_key_bindings.screen_mode == 0) {
        ShowLabel(manager, room, 0x1f, 0x2e);
        ShowLabel(manager, room, 0x20, 0x2f);
    } else if (g_key_bindings.screen_mode == 1) {
        ShowLabel(manager, room, 0x1f, 0x30);
        ShowLabel(manager, room, 0x20, 0x31);
    } else {
        ShowLabel(manager, room, 0x1f, 0x2c);
        ShowLabel(manager, room, 0x20, 0x2d);
    }
}

static __forceinline void ShowScreenMode(Title* room) {
    AnmLookupContext* manager = reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl);
    ShowModeLabels(manager, room);
}

// Restart the cursor animation of slot 1.
static __forceinline void RunCursorSlot2(Title* room) {
    AnimationManager_SetStopFrameAndRun(
        3, reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl),
        room->animation_slots[1]);
}

enum OptionsPhase {
    OPT_PHASE_ENTER = 0,
    OPT_PHASE_WAIT_OPEN = 1,
    OPT_PHASE_ACTIVE = 2,
    OPT_PHASE_TRANSITION = 4
};

enum OptionsItem {
    OPT_ITEM_SCREEN_MODE = 0,
    OPT_ITEM_MUSIC_VOLUME = 1,
    OPT_ITEM_SOUND_VOLUME = 2,
    OPT_ITEM_KEY_CONFIG = 3,
    OPT_ITEM_DEFAULTS = 4,
    OPT_ITEM_QUIT = 5,
    OPT_ITEM_COUNT = 6
};

enum OptionsKeyMask {
    OPT_KEY_BOMB_CANCEL = 0x0002,
    OPT_KEY_ESC = 0x0008,
    OPT_KEY_UP = 0x0010,
    OPT_KEY_DOWN = 0x0020,
    OPT_KEY_LEFT = 0x0040,
    OPT_KEY_RIGHT = 0x0080,
    OPT_KEY_CONFIRM = 0x1001
};

enum OptionsSfx {
    OPT_SFX_TEST = 4,
    OPT_SFX_CONFIRM = 10,
    OPT_SFX_CANCEL = 11,
    OPT_SFX_MOVE = 12
};

enum OptionsTargetMode {
    OPT_TARGET_MAIN_MENU = 2,
    OPT_TARGET_KEY_CONFIG = 5
};

#pragma code_seg(".text$0042d920_fn")
__declspec(noinline) int __stdcall TitleOptions(Title* room) {
    switch (room->phase) {
    case OPT_PHASE_ENTER:
        room->cursor.item_count = OPT_ITEM_COUNT;
        SelectItem4(room->cursor, OPT_ITEM_SCREEN_MODE);
        Title_InstallAnimationSlot(room, 1);
        RefreshOptions2(room);
        room->SetTimerTarget(OPT_PHASE_WAIT_OPEN);
    case OPT_PHASE_WAIT_OPEN:
        if (room->timer.current > 6) {
            room->SetTimerTarget(OPT_PHASE_ACTIVE);
            RunCursorSlot2(room);
            ShowScreenMode(room);
            room->SetSlotFrame(1, room->cursor.selection + 0x11);
        }
        break;
    case OPT_PHASE_ACTIVE: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(OPT_KEY_UP)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(OPT_KEY_DOWN)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            application_state.sound.Queue(OPT_SFX_MOVE, 0);
            RunCursorSlot2(room);
            room->SetSlotFrame(1, room->cursor.selection + 7);
        }
        if (g_input_keys_held & OPT_KEY_ESC)
            goto cancel;
        if (g_input_keys_held & OPT_KEY_BOMB_CANCEL) {
        cancel:
            if (room->cursor.selection == OPT_ITEM_QUIT) {
                room->SetSlotFrame(1, 6);
                application_state.sound.Queue(OPT_SFX_CANCEL, 0);
                room->SetTimerTarget(OPT_PHASE_TRANSITION);
            } else {
                application_state.sound.Queue(OPT_SFX_CANCEL, 0);
                SelectItem4(room->cursor, OPT_ITEM_QUIT);
                reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(1);
                room->SetSlotFrame(1, room->cursor.selection + 7);
            }
        } else {
            // The test sound of the sound volume item.
            if (room->cursor.selection == OPT_ITEM_SOUND_VOLUME
                    && reinterpret_cast<FrameCounterPair*>(&room->timer)->AtInterval(60))
                application_state.sound.Queue(OPT_SFX_TEST, 0);
            AnmLookupContext* manager;
            if ((short)g_input_keys_raw.InputMaskActive(OPT_KEY_LEFT)) {
                manager = reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl);
                switch (room->cursor.selection) {
                case OPT_ITEM_SCREEN_MODE:
                    if (g_key_bindings.screen_mode > 0)
                        --g_key_bindings.screen_mode;
                    else
                        g_key_bindings.screen_mode = 2;
                    ShowModeLabels(manager, room);
                    application_state.sound.Queue(OPT_SFX_MOVE, 0);
                    break;
                case OPT_ITEM_MUSIC_VOLUME:
                    // MATCH: both paths converge on the label refresh; MSVC's LTCG tail-duplicates
                    // the call into each branch, which keeps the `mov edi,ebp` argument
                    // setup per-branch and the decrement a split `add al,0xfb` instead of
                    // the folded `add byte ptr [mem],0xfb` a shared call site would fold to.
                    if (g_key_bindings.music_volume < 5) {
                        g_key_bindings.music_volume = 0;
                        goto refresh_music;
                    }
                    g_key_bindings.music_volume += 0xFB;
                refresh_music:
                    RefreshOptions2(room);
                    break;
                case OPT_ITEM_SOUND_VOLUME:
                    if (g_key_bindings.sound_volume < 5) {
                        g_key_bindings.sound_volume = 0;
                        goto refresh_sound;
                    }
                    g_key_bindings.sound_volume += 0xFB;
                refresh_sound:
                    RefreshOptions2(room);
                    break;
                }
            }
            else
                manager = reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl);
            if ((short)g_input_keys_raw.InputMaskActive(OPT_KEY_RIGHT)) {
                switch (room->cursor.selection) {
                case OPT_ITEM_SCREEN_MODE:
                    if (g_key_bindings.screen_mode < 2)
                        ++g_key_bindings.screen_mode;
                    else
                        g_key_bindings.screen_mode = 0;
                    application_state.sound.Queue(OPT_SFX_MOVE, 0);
                    ShowModeLabels(manager, room);
                    break;
                case OPT_ITEM_MUSIC_VOLUME:
                    g_key_bindings.music_volume += 5;
                    if (g_key_bindings.music_volume > 100)
                        g_key_bindings.music_volume = 100;
                    RefreshOptions2(room);
                    break;
                case OPT_ITEM_SOUND_VOLUME:
                    g_key_bindings.sound_volume += 5;
                    if (g_key_bindings.sound_volume > 100)
                        g_key_bindings.sound_volume = 100;
                    RefreshOptions2(room);
                    break;
                }
            }
            if (g_input_keys_held & OPT_KEY_CONFIRM) {
                switch (room->cursor.selection) {
                case OPT_ITEM_QUIT:
                    room->SetSlotFrame(1, 6);
                    application_state.sound.Queue(OPT_SFX_CANCEL, 0);
                    room->SetTimerTarget(OPT_PHASE_TRANSITION);
                    break;
                case OPT_ITEM_DEFAULTS:
                    g_key_bindings.music_volume = 100;
                    g_key_bindings.sound_volume = 80;
                    g_key_bindings.screen_mode = 0;
                    RefreshOptions2(room);
                    ShowModeLabels(manager, room);
                    application_state.sound.Queue(OPT_SFX_CONFIRM, 0);
                    break;
                case OPT_ITEM_KEY_CONFIG:
                    room->SetSlotFrame(1, 6);
                    application_state.sound.Queue(OPT_SFX_CONFIRM, 0);
                    room->SetTimerTarget(OPT_PHASE_TRANSITION);
                    break;
                }
            }
        }
        break;
    }
    case OPT_PHASE_TRANSITION:
        if (room->timer.current >= 10) {
            MenuCursor* cursor = &room->cursor;
            switch (cursor->selection) {
            case OPT_ITEM_KEY_CONFIG:
                room->DisableTimerWithOwner(OPT_TARGET_KEY_CONFIG);
                cursor->PushSelection();
                break;
            case OPT_ITEM_QUIT:
                reinterpret_cast<TitleAnimationSlotView*>(room)->StopSlot(0x5a);
                reinterpret_cast<TitleAnimationSlotView*>(room)->StopSlot(0x5b);
                room->DisableTimerWithOwner(OPT_TARGET_MAIN_MENU);
                cursor->PopSelection();
                break;
            }
        }
        break;
    }
    return 1;
}
#pragma code_seg()
