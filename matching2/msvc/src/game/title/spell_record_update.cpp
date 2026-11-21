// 0x00431EE0..0x0043268F: spell card record screen of the title menu (and its
// four-entry phase table).
//
// Phase 0 builds the screen for the first shot type and the Normal difficulty
// and runs phase 1 on the same frame.  Phase 1 waits seven frames.  Phase 2
// moves between difficulties (left/right) and shot types (up/down); confirm
// steps through the pages of ten cards, the first page being the summary.
// With Extra and the third shot type selected, typing the 22-key sequence on
// the keyboard unlocks every stage.  Cancel leaves through phase 3, which
// returns to the main menu after six frames.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (build_support/layout/ltcg/difficulty_select_update.json).
#include <string.h>

#include "th10/game/spell_record_update.hpp"

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem10(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// The number of pages a difficulty needs: the summary and ten cards a page.
static __forceinline int PageCount(int difficulty) {
    return (SpellCards_CountOfDifficulty(difficulty) + 9) / 10 + 1;
}

// The animation a handle refers to, searching both of the manager's lists
// (0x004491C0 as it is inlined in phase 2).
static __forceinline RecoveryMusicVm* FindAnimation2(
        RecoveryLookupContext* context, unsigned int handle) {
    if (handle == 0)
        return 0;
    RecoveryLookupNode* node;
    for (node = context->primary; node != 0; node = node->next)
        if (reinterpret_cast<RecoveryMusicVm*>(node->object)->id == handle)
            return reinterpret_cast<RecoveryMusicVm*>(node->object);
    for (node = context->secondary; node != 0; node = node->next)
        if (reinterpret_cast<RecoveryMusicVm*>(node->object)->id == handle)
            return reinterpret_cast<RecoveryMusicVm*>(node->object);
    return 0;
}

// Stop an animation and its children at a frame.
static __forceinline void SetTreeFrame(RecoveryMusicVm* object, unsigned short frame) {
    if (object != 0) {
        object->stop_frame = frame;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild* child = object->children; child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}

enum SpellRecordPhase {
    SPELL_PHASE_ENTER = 0,
    SPELL_PHASE_WAIT_OPEN = 1,
    SPELL_PHASE_ACTIVE = 2,
    SPELL_PHASE_EXIT = 3
};

enum SpellRecordConstants {
    SPELL_SHOT_TOTAL = 6,
    SPELL_DIFFICULTY_COUNT = 5,
    SPELL_DIFFICULTY_NORMAL = 1,
    SPELL_DIFFICULTY_EXTRA = 4,
    SPELL_LINES_PER_PAGE = 10,
    SPELL_UNLOCK_SEQ_LEN = 22,
    SPELL_KEY_CANCEL = 0x000A,
    SPELL_KEY_UP = 0x0010,
    SPELL_KEY_DOWN = 0x0020,
    SPELL_KEY_LEFT = 0x0040,
    SPELL_KEY_RIGHT = 0x0080,
    SPELL_KEY_CONFIRM = 0x1001,
    SPELL_KEY_RESET_SEQ = 0x160B,
    SPELL_SFX_CONFIRM = 10,
    SPELL_SFX_CANCEL = 11,
    SPELL_SFX_MOVE = 12,
    SPELL_SFX_UNLOCK_ALL = 44,
    SPELL_TARGET_MAIN_MENU = 2
};

#pragma code_seg(".text$00431ee0_fn")
__declspec(noinline) int __stdcall TitleMode11(Title* room) {
    TitleSpellRecordView* records = reinterpret_cast<TitleSpellRecordView*>(room);
    void* handle;
    void* line_handle;
    switch (room->phase) {
    case SPELL_PHASE_ENTER: {
        room->cursor.item_count = SPELL_SHOT_TOTAL;
        SelectItem10(room->cursor, 0);
        records->difficulty.item_count = SPELL_DIFFICULTY_COUNT;
        SelectItem10(records->difficulty, SPELL_DIFFICULTY_NORMAL);
        records->difficulty.wrap = 1;
        records->page.item_count = PageCount(records->difficulty.selection);
        SelectItem10(records->page, 0);
        MenuCursor* page = &records->page;
        page->wrap = 1;
        EnsureTitleMenuBackdrop(room, handle);
        RecoveryMusicInstallSlot(room, 102);
        room->SetTimerTarget(SPELL_PHASE_WAIT_OPEN);
        RecoveryMusicInstallSlot(room, room->cursor.selection / 3 + 152);
        RecoveryMusicInstallSlot(room, room->cursor.selection + 154);
        RecoveryMusicInstallSlot(room, records->difficulty.selection + 160);
        RecoveryMusicInstallSlot(room, 168);
        RecoveryMusicInstallSlot(room, 169);
        RecoveryMusicInstallSlot(room, 170);
        RecoveryMusicInstallSlot(room, 171);
        RecoveryMusicInstallSlot(room, 165);
        RecoveryMusicInstallSlot(room, 166);
        RecoveryMusicInstallSlot(room, 167);
        RecoveryMusicInstallSlot(room, 172);
    }
    case SPELL_PHASE_WAIT_OPEN:
        if (room->timer.current > 6)
            room->SetTimerTarget(SPELL_PHASE_ACTIVE);
        break;
    case SPELL_PHASE_ACTIVE: {
        room->cursor.previous_selection = room->cursor.selection;
        MenuCursor* difficulty = &records->difficulty;
        difficulty->previous_selection = difficulty->selection;
        records->page.previous_selection = records->page.selection;
        if ((short)g_input_keys_raw.InputMaskActive(SPELL_KEY_UP)) {
            difficulty->Advance(-1);
            AnimationManager_SetStopFrameAndRun(
                2, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
                room->animation_slots[170]);
        }
        if ((short)g_input_keys_raw.InputMaskActive(SPELL_KEY_DOWN)) {
            difficulty->Advance(1);
            AnimationManager_SetStopFrameAndRun(
                2, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
                room->animation_slots[171]);
        }
        if (difficulty->previous_selection != difficulty->selection) {
            g_sound_manager.Queue(SPELL_SFX_MOVE, 0);
            room->ClearAnimationSlot(records->difficulty.previous_selection + 160);
            RecoveryMusicInstallSlot(room, difficulty->selection + 160);
            if (records->page.selection > 0) {
                SelectItem10(records->page, 1);
                reinterpret_cast<TitleDrawView*>(room)->BuildSpellList();
            }
            records->page.item_count = PageCount(difficulty->selection);
        }
        if ((short)g_input_keys_raw.InputMaskActive(SPELL_KEY_LEFT)) {
            room->cursor.Advance(-1);
            AnimationManager_SetStopFrameAndRun(
                2, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
                room->animation_slots[168]);
        }
        if ((short)g_input_keys_raw.InputMaskActive(SPELL_KEY_RIGHT)) {
            room->cursor.Advance(1);
            AnimationManager_SetStopFrameAndRun(
                2, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
                room->animation_slots[169]);
        }
        if (room->cursor.previous_selection != room->cursor.selection) {
            g_sound_manager.Queue(SPELL_SFX_MOVE, 0);
            if (room->cursor.selection / 3 != room->cursor.previous_selection / 3) {
                room->ClearAnimationSlot(room->cursor.previous_selection / 3 + 152);
                RecoveryMusicInstallSlot(room, room->cursor.selection / 3 + 152);
            }
            room->ClearAnimationSlot(room->cursor.previous_selection + 154);
            RecoveryMusicInstallSlot(room, room->cursor.selection + 154);
            if (records->page.selection > 0)
                reinterpret_cast<TitleDrawView*>(room)->BuildSpellList();
        }
        if (g_input_keys_held & SPELL_KEY_CONFIRM) {
            if (records->page.selection == 0) {
                int line = 0;
                do {
                    void* resource = g_ascii_manager->text_resource;
                    void** result = AnimationManager_CreatePrimaryBack(resource, &line_handle, line + 23, 15);
                    records->lines[line].value = reinterpret_cast<unsigned int>(*result);
                    ++line;
                } while (line < SPELL_LINES_PER_PAGE);
            }
            MenuCursor* page = &records->page;
            page->Advance(1);
            if (page->selection == 0) {
                for (int line = 0; line < SPELL_LINES_PER_PAGE; ++line)
                    RecoveryMusicStopHandle(&records->lines[line]);
            } else {
                reinterpret_cast<TitleDrawView*>(room)->BuildSpellList();
            }
            g_sound_manager.Queue(SPELL_SFX_CONFIRM, 0);
        }
        if (records->difficulty.selection == SPELL_DIFFICULTY_EXTRA && room->cursor.selection == 2) {
            // Any game key restarts the secret unlock-all-stages sequence.
            if (g_input_keys_held & SPELL_KEY_RESET_SEQ) {
                g_spell_seq_progress = 0;
                g_spell_seq_elapsed = 0;
            }
            memcpy(g_keys_previous, g_keys_current, sizeof(g_keys_previous));
            if (Input_UpdateKeyboardState(g_keys_current)) {
                for (int key = 0; key < 256; ++key)
                    g_spell_seq_keys[key] = (g_keys_previous[key] ^ g_keys_current[key]) & g_keys_current[key];
                if (g_spell_seq_progress >= SPELL_UNLOCK_SEQ_LEN) {
                    UnlockAllStages2(reinterpret_cast<GameProgress3*>(g_score));
                    g_sound_manager.Queue(SPELL_SFX_UNLOCK_ALL, 0);
                    g_spell_seq_progress = 0;
                } else if (g_spell_seq_keys[g_spell_seq_codes[g_spell_seq_progress]] & 0x80) {
                    ++g_spell_seq_progress;
                    g_spell_seq_elapsed = 0;
                } else {
                    unsigned char any = 0;
                    for (int key = 0; key < 57; ++key)
                        any |= g_spell_seq_keys[key];
                    if (any & 0x80)
                        g_spell_seq_progress = 0;
                }
            }
            ++g_spell_seq_elapsed;
            if (g_spell_seq_elapsed > 300) {
                g_spell_seq_progress = 0;
                g_spell_seq_elapsed = 0;
            }
        }
        if (g_input_keys_held & SPELL_KEY_CANCEL) {
            room->SetTimerTarget(SPELL_PHASE_EXIT);
            g_sound_manager.Queue(SPELL_SFX_CANCEL, 0);
            room->ClearAnimationSlot(records->difficulty.selection + 160);
            room->ClearAnimationSlot(room->cursor.selection + 154);
            room->ClearAnimationSlot(room->cursor.selection / 3 + 152);
            room->ClearAnimationSlot(168);
            room->ClearAnimationSlot(169);
            room->ClearAnimationSlot(170);
            room->ClearAnimationSlot(171);
            room->ClearAnimationSlot(165);
            room->ClearAnimationSlot(166);
            room->ClearAnimationSlot(167);
            room->ClearAnimationSlot(172);
            for (int line = 0; line < SPELL_LINES_PER_PAGE; ++line)
                SetTreeFrame(
                    FindAnimation2(reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl),
                                           records->lines[line].value), 1);
        }
        break;
    }
    case SPELL_PHASE_EXIT:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(102);
            room->SetSlotFrame(90, 8);
            room->SetSlotFrame(91, 8);
            room->ClearAnimationSlot(94);
            RecoveryMusicStopHandle(&room->fallback_handle);
            room->DisableTimerWithOwner(SPELL_TARGET_MAIN_MENU);
            room->cursor.PopSelection();
        }
        break;
    }
    return 1;
}
#pragma code_seg()
