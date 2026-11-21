// 0x00422C80: update the pause menu, restart confirmation and result choice.
#include "th10/game/pause_choice/state.hpp"

__forceinline short ChoiceInputActive(const KeyRepeatState* input, unsigned short mask) {
    if ((input->unknown_06 & mask) != 0) return 1;
    if ((input->pressed & mask) != 0) return 1;
    return 0;
}

enum PausePhaseId {
    PAUSE_CLOSED = 0,
    PAUSE_OPENING = 1,
    PAUSE_MENU = 2,
    PAUSE_CLOSING = 3,
    PAUSE_CONFIRM_OPEN = 4,
    PAUSE_CONFIRM_RESOLVE = 5
};

enum PauseKeyMask {
    PAUSE_KEY_ESC = 0x0008,
    PAUSE_KEY_UP = 0x0010,
    PAUSE_KEY_DOWN = 0x0020,
    PAUSE_KEY_QUICK_RETRY = 0x0200,
    PAUSE_KEY_CONFIRM = 0x1001,
    PAUSE_KEY_QUICK_QUIT = 0x4000
};

enum PauseSfxId {
    PAUSE_SFX_CONFIRM = 10,
    PAUSE_SFX_MOVE = 12
};

#pragma code_seg(".text$30choice")
extern "C" __declspec(noinline) void __stdcall PauseMenu_Update(PauseChoiceState* state) {
    switch (state->phase) {
    case PAUSE_OPENING:
        if (state->timer.field_04 >= 10) {
            state->phase = PAUSE_MENU;
            state->cursor.item_count = g_game->replay_mode ? 2 : 3;
            state->cursor.wrap = 1;
            state->cursor.Select(0);
            state->background.SetStopFrame((unsigned short)(state->cursor.selection + 7));
            return;
        }
        break;
    case PAUSE_MENU: {
        PauseChoiceCursor* cursor = &state->cursor;
        cursor->previous_selection = cursor->selection;
        if (ChoiceInputActive(&g_input_keys_raw, PAUSE_KEY_UP))
            cursor->Advance(-1);
        if (ChoiceInputActive(&g_input_keys_raw, PAUSE_KEY_DOWN))
            cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            state->background.SetStopFrame((unsigned short)(cursor->selection + 7));
            g_sound_manager.Queue(PAUSE_SFX_MOVE, 0);
        }
        if (g_input_keys_held & PAUSE_KEY_CONFIRM) {
            g_sound_manager.Queue(PAUSE_SFX_CONFIRM, 0);
            switch (cursor->selection) {
            case 2:
                state->background.FindChildRef(117).StopAtFrame6();
                state->phase = PAUSE_CONFIRM_OPEN;
                break;
            case 1:
                state->background.FindChildRef(116).StopAtFrame6();
                state->phase = g_game->replay_mode ? PAUSE_CLOSING : PAUSE_CONFIRM_OPEN;
                break;
            case 0:
                state->cursor_animation.StopAtFrame1();
                state->background.StopAtFrame1();
                state->pause_animation.StopAtFrame1();
                state->phase = PAUSE_CLOSING;
                break;
            }
            state->timer.SetSchedulerValue(0);
        }
        if (g_input_keys_held & PAUSE_KEY_QUICK_QUIT) {
            g_sound_manager.Queue(PAUSE_SFX_CONFIRM, 0);
            state->background.FindChildRef(117).StopAtFrame6();
            state->phase = PAUSE_CLOSING;
            state->timer.SetSchedulerValue(0);
            state->cursor.Select(2);
            state->cursor_animation.StopAtFrame1();
        }
        if (g_input_keys_held & PAUSE_KEY_QUICK_RETRY) {
            g_sound_manager.Queue(PAUSE_SFX_CONFIRM, 0);
            state->background.FindChildRef(116).StopAtFrame6();
            state->phase = PAUSE_CLOSING;
            state->timer.SetSchedulerValue(0);
            state->cursor.Select(1);
        }
        goto escape;
    }
    case PAUSE_CONFIRM_OPEN: {
        if (state->timer.field_04 < 20) return;
        if (state->timer.field_04 == 20) {
            state->cursor.PushSelection();
            state->cursor.item_count = 2;
            state->cursor.wrap = 1;
            state->cursor.Select(1);
            state->background.SetStopFrame(14);
        }
        if (state->timer.field_04 < 30) return;
        if (state->timer.field_04 == 30)
            state->background.SetStopFrame((unsigned short)(state->cursor.selection + 15));
        PauseChoiceCursor* cursor = &state->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)g_input_keys_raw.InputMaskActive(PAUSE_KEY_UP)) cursor->Advance(-1);
        if ((short)g_input_keys_raw.InputMaskActive(PAUSE_KEY_DOWN)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            state->background.SetStopFrame((unsigned short)(cursor->selection + 15));
            g_sound_manager.Queue(PAUSE_SFX_MOVE, 0);
        }
        if (g_input_keys_held & PAUSE_KEY_CONFIRM) {
            g_sound_manager.Queue(PAUSE_SFX_CONFIRM, 0);
            switch (cursor->selection) {
            case 1:
                state->background.FindChildRef(120).StopAtFrame6();
                state->phase = PAUSE_CONFIRM_RESOLVE;
                break;
            case 0:
                state->background.FindChildRef(119).StopAtFrame6();
                state->phase = PAUSE_CONFIRM_RESOLVE;
                break;
            }
            state->timer.SetSchedulerValue(0);
        }
        goto escape;
    }
    case PAUSE_CONFIRM_RESOLVE:
        if (state->timer.field_04 < 20) break;
        switch (state->cursor.selection) {
        case 1: {
            state->cursor.PopSelection();
            short frame = (short)state->cursor.selection;
            frame += 7;
            state->background.SetStopFrame(frame);
            state->phase = PAUSE_MENU;
            state->timer.SetSchedulerValue(0);
            return;
        }
        case 0:
            state->cursor_animation.StopAtFrame1();
            state->background.StopAtFrame1();
            state->phase = PAUSE_CLOSING;
            state->cursor.PopSelection();
            break;
        }
        state->timer.SetSchedulerValue(0);
        return;
    case PAUSE_CLOSING:
        if (state->timer.field_04 < 12) break;
        state->phase = PAUSE_CLOSED;
        switch (state->cursor.selection) {
        case 2:
            state->background.StopAtFrame1();
            g_main_state = 10;
            return;
        case 1:
            state->cursor_animation.StopAtFrame1();
            state->background.StopAtFrame1();
            SetInputMode(&g_application, 4);
            return;
        case 0:
            reinterpret_cast<PauseOwner*>(state)->Unpause();
            break;
        }
    }
    return;
    escape:
        if (g_input_keys_held & PAUSE_KEY_ESC) {
            state->cursor.Select(0);
            state->cursor_animation.StopAtFrame1();
            state->background.StopAtFrame1();
            state->pause_animation.StopAtFrame1();
            state->phase = PAUSE_CLOSING;
            state->timer.SetSchedulerValue(0);
            return;
        }
}
#pragma code_seg()
