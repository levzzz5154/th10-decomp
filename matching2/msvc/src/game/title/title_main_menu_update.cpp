// 0x0042D420..0x0042D91F: main menu of the title screen (its five-entry
// phase table and the two eight-entry item tables).
//
// Phase 0 offers the eight items (the extra start is disabled until some
// shot type has cleared the game), puts the cursor on "practice" when the
// game comes back from one, installs the backdrop and the cursor animation
// and runs phase 1 on the same frame.  Phase 1 waits eleven frames and starts
// the cursor animation.  Phase 2 moves the cursor; cancel moves it to "quit"
// (and quits when it is already there), confirm starts the leaving animation
// of the chosen item.  Phase 4 opens the chosen screen after twenty frames.
//
// The room arrives in EBX from the title dispatcher (0x0042CDF0); the handler
// is linked with the dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update.json).
//
// Shapes that are load-bearing (each measured against the image):
//
//  * Cancel on "quit" jumps into the quit case of the confirm switch.  As a
//    second copy of the two calls the sound request is hoisted above the
//    selection test.
//  * The room is loaded again for the slot restart that follows
//    SetTimerTarget in the "replay" case although that function leaves EAX
//    alone: SetTimerTarget is defined in the room's class, and the compiler
//    keeps no register summary for the out-of-line copy of an in-class member.
#include "th10/game/title_main_menu_update.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem3(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// MenuCursor::DisableItem (0x00434BC0) as it is inlined here.
static __forceinline void DisableItem2(MenuCursor& cursor, int item) {
    cursor.disabled_items[cursor.disabled_count] = item;
    ++cursor.disabled_count;
}

// Restart the cursor animation of slot 0.
static __forceinline void RunCursorSlot(Title* room) {
    AnimationManager_SetStopFrameAndRun(
        3, reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl),
        room->animation_slots[0]);
}

enum MainMenuPhase {
    MAIN_MENU_ENTER = 0,
    MAIN_MENU_WAIT_OPEN = 1,
    MAIN_MENU_ACTIVE = 2,
    MAIN_MENU_TRANSITION = 4
};

enum MainMenuItem {
    MENU_ITEM_START = 0,
    MENU_ITEM_EXTRA_START = 1,
    MENU_ITEM_PRACTICE_START = 2,
    MENU_ITEM_REPLAY = 3,
    MENU_ITEM_PLAYER_DATA = 4,
    MENU_ITEM_MUSIC_ROOM = 5,
    MENU_ITEM_OPTIONS = 6,
    MENU_ITEM_QUIT = 7,
    MENU_ITEM_COUNT = 8
};

enum MainMenuKeyMask {
    MAIN_KEY_CANCEL = 0x000A,
    MAIN_KEY_UP = 0x0010,
    MAIN_KEY_DOWN = 0x0020,
    MAIN_KEY_CONFIRM = 0x1001
};

enum MainMenuSfx {
    MAIN_SFX_CONFIRM = 10,
    MAIN_SFX_CANCEL = 11,
    MAIN_SFX_MOVE = 12
};

enum MainMenuTargetMode {
    MAIN_TARGET_LEAVE = 3,
    MAIN_TARGET_OPTIONS = 4,
    MAIN_TARGET_DIFFICULTY = 6,
    MAIN_TARGET_SPELL_RECORD = 11,
    MAIN_TARGET_REPLAY_SELECT = 12,
    MAIN_TARGET_MUSIC_ROOM = 14
};

enum MainMenuConstants {
    MAIN_GLOBAL_FLAG_PRACTICE = 0x10,
    MAIN_DIFFICULTY_NORMAL = 1,
    MAIN_DIFFICULTY_EXTRA = 4
};

#pragma code_seg(".text$0042d420_fn")
__declspec(noinline) int __stdcall TitleMainMenu(Title* room) {
    switch (room->phase) {
    case MAIN_MENU_ENTER:
        room->cursor.item_count = MENU_ITEM_COUNT;
        if (!reinterpret_cast<ScoreFileProgress*>(g_score)->HasAnyClear())
            DisableItem2(room->cursor, MENU_ITEM_EXTRA_START);
        if (g_globals_flags & MAIN_GLOBAL_FLAG_PRACTICE) {
            SelectItem3(room->cursor, MENU_ITEM_PRACTICE_START);
            g_globals_flags &= ~(unsigned int)MAIN_GLOBAL_FLAG_PRACTICE;
        }
        if (reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(
                reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl),
                room->animation_slots[88]) == 0)
            RecoveryMusicInstallSlot(room, 88);
        RecoveryMusicInstallSlot(room, 0);
        room->SetTimerTarget(MAIN_MENU_WAIT_OPEN);
    case MAIN_MENU_WAIT_OPEN:
        if (room->timer.current > 10) {
            room->SetTimerTarget(MAIN_MENU_ACTIVE);
            RunCursorSlot(room);
            room->SetSlotFrame(0, room->cursor.selection + 0x11);
        }
        break;
    case MAIN_MENU_ACTIVE: {
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(MAIN_KEY_UP)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(MAIN_KEY_DOWN)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            g_sound_manager.Queue(MAIN_SFX_MOVE, 0);
            RunCursorSlot(room);
            room->SetSlotFrame(0, cursor->selection + 7);
        }
        if (g_input_keys_held & MAIN_KEY_CANCEL) {
            if (cursor->selection == MENU_ITEM_QUIT)
                goto quit;
            g_sound_manager.Queue(MAIN_SFX_CANCEL, 0);
            SelectItem3(*cursor, MENU_ITEM_QUIT);
            reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(0);
            room->SetSlotFrame(0, cursor->selection + 7);
        }
        if (g_input_keys_held & MAIN_KEY_CONFIRM) {
            room->SetSlotFrame(0, 6);
            switch (cursor->selection) {
            case MENU_ITEM_START:
            case MENU_ITEM_EXTRA_START:
            case MENU_ITEM_PRACTICE_START:
            case MENU_ITEM_REPLAY:
            case MENU_ITEM_PLAYER_DATA:
                g_sound_manager.Queue(MAIN_SFX_CONFIRM, 0);
                room->SetSlotFrame(0x5a, 7);
                room->SetSlotFrame(0x5b, 7);
                room->SetTimerTarget(MAIN_MENU_TRANSITION);
                break;
            case MENU_ITEM_MUSIC_ROOM:
                g_sound_manager.Queue(MAIN_SFX_CONFIRM, 0);
                room->SetSlotFrame(0x5a, 7);
                room->SetSlotFrame(0x5b, 7);
                room->SetTimerTarget(MAIN_MENU_TRANSITION);
                g_sound_manager.Queue(MAIN_SFX_CONFIRM, 0);
                break;
            case MENU_ITEM_OPTIONS:
                g_sound_manager.Queue(MAIN_SFX_CONFIRM, 0);
                room->SetTimerTarget(MAIN_MENU_TRANSITION);
                reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(0x5a);
                reinterpret_cast<TitleAnimationSlotView*>(room)->RestartSlot(0x5b);
                break;
            case MENU_ITEM_QUIT:
            quit:
                g_sound_manager.Queue(MAIN_SFX_CANCEL, 0);
                room->SetTimerTarget(MAIN_MENU_TRANSITION);
                break;
            }
        }
        break;
    }
    case MAIN_MENU_TRANSITION:
        if (room->timer.current >= 20) {
            MenuCursor* cursor = &room->cursor;
            switch (cursor->selection) {
            case MENU_ITEM_START:
                g_globals_flags &= ~(unsigned int)MAIN_GLOBAL_FLAG_PRACTICE;
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(MAIN_TARGET_DIFFICULTY);
                cursor->PushSelection();
                if (g_globals_difficulty >= MAIN_DIFFICULTY_EXTRA)
                    g_globals_difficulty = MAIN_DIFFICULTY_NORMAL;
                UpdateBoundedCounter(g_globals_difficulty, reinterpret_cast<unsigned int*>(cursor));
                break;
            case MENU_ITEM_EXTRA_START:
                g_globals_flags &= ~(unsigned int)MAIN_GLOBAL_FLAG_PRACTICE;
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(MAIN_TARGET_DIFFICULTY);
                cursor->PushSelection();
                reinterpret_cast<TitleDifficultyView*>(room)->saved_difficulty = g_globals_difficulty;
                g_globals_difficulty = MAIN_DIFFICULTY_EXTRA;
                SelectItem3(*cursor, 0);
                break;
            case MENU_ITEM_PRACTICE_START:
                g_globals_flags |= MAIN_GLOBAL_FLAG_PRACTICE;
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(MAIN_TARGET_DIFFICULTY);
                cursor->PushSelection();
                if (g_globals_difficulty >= MAIN_DIFFICULTY_EXTRA)
                    g_globals_difficulty = MAIN_DIFFICULTY_NORMAL;
                UpdateBoundedCounter(g_globals_difficulty, reinterpret_cast<unsigned int*>(cursor));
                break;
            case MENU_ITEM_REPLAY:
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(MAIN_TARGET_REPLAY_SELECT);
                cursor->PushSelection();
                break;
            case MENU_ITEM_PLAYER_DATA:
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(MAIN_TARGET_SPELL_RECORD);
                cursor->PushSelection();
                break;
            case MENU_ITEM_MUSIC_ROOM:
                room->ClearAnimationSlot(88);
                room->DisableTimerWithOwner(MAIN_TARGET_MUSIC_ROOM);
                cursor->PushSelection();
                break;
            case MENU_ITEM_OPTIONS:
                room->DisableTimerWithOwner(MAIN_TARGET_OPTIONS);
                cursor->PushSelection();
                break;
            case MENU_ITEM_QUIT:
                room->DisableTimerWithOwner(MAIN_TARGET_LEAVE);
                break;
            }
        }
        break;
    }
    return 1;
}
#pragma code_seg()
