// 0x00422C80: update the pause menu, restart confirmation and result choice.
#include "th10/game/pause_choice_00422c80/state.hpp"

__forceinline short ChoiceInputActive(const KeyRepeatState* input, unsigned short mask) {
    if ((input->unknown_06 & mask) != 0) return 1;
    if ((input->pressed & mask) != 0) return 1;
    return 0;
}

#pragma code_seg(".text$30choice")
extern "C" __declspec(noinline) void __stdcall PauseMenu_Update_00422c80(PauseChoiceState* state) {
    switch (state->phase) {
    case 1:
        if (state->timer.field_04 >= 10) {
            state->phase = 2;
            state->cursor.item_count = g_game->replay_mode ? 2 : 3;
            state->cursor.wrap = 1;
            state->cursor.Select(0);
            state->background.SetStopFrame((unsigned short)(state->cursor.selection + 7));
            return;
        }
        break;
    case 2: {
        PauseChoiceCursor_00422c80* cursor = &state->cursor;
        cursor->previous_selection = cursor->selection;
        if (ChoiceInputActive(&data_00474e30, 0x10))
            cursor->Advance(-1);
        if (ChoiceInputActive(&data_00474e30, 0x20))
            cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            state->background.SetStopFrame((unsigned short)(cursor->selection + 7));
            data_00492590.Queue(12, 0);
        }
        if (data_00474e36 & 0x1001) {
            data_00492590.Queue(10, 0);
            switch (cursor->selection) {
            case 2:
                state->background.FindChildRef(117).StopAtFrame6();
                state->phase = 4;
                break;
            case 1:
                state->background.FindChildRef(116).StopAtFrame6();
                state->phase = g_game->replay_mode ? 3 : 4;
                break;
            case 0:
                state->cursor_animation.StopAtFrame1();
                state->background.StopAtFrame1();
                state->pause_animation.StopAtFrame1();
                state->phase = 3;
                break;
            }
            state->timer.SetSchedulerValue(0);
        }
        if (data_00474e36 & 0x4000) {
            data_00492590.Queue(10, 0);
            state->background.FindChildRef(117).StopAtFrame6();
            state->phase = 3;
            state->timer.SetSchedulerValue(0);
            state->cursor.Select(2);
            state->cursor_animation.StopAtFrame1();
        }
        if (data_00474e36 & 0x200) {
            data_00492590.Queue(10, 0);
            state->background.FindChildRef(116).StopAtFrame6();
            state->phase = 3;
            state->timer.SetSchedulerValue(0);
            state->cursor.Select(1);
        }
        goto escape;
    }
    case 4: {
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
        PauseChoiceCursor_00422c80* cursor = &state->cursor;
        cursor->previous_selection = cursor->selection;
        if ((short)data_00474e30.InputMaskActive(0x10)) cursor->Advance(-1);
        if ((short)data_00474e30.InputMaskActive(0x20)) cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            state->background.SetStopFrame((unsigned short)(cursor->selection + 15));
            data_00492590.Queue(12, 0);
        }
        if (data_00474e36 & 0x1001) {
            data_00492590.Queue(10, 0);
            switch (cursor->selection) {
            case 1:
                state->background.FindChildRef(120).StopAtFrame6();
                state->phase = 5;
                break;
            case 0:
                state->background.FindChildRef(119).StopAtFrame6();
                state->phase = 5;
                break;
            }
            state->timer.SetSchedulerValue(0);
        }
        goto escape;
    }
    case 5:
        if (state->timer.field_04 < 20) break;
        switch (state->cursor.selection) {
        case 1: {
            state->cursor.PopSelection();
            short frame = (short)state->cursor.selection;
            frame += 7;
            state->background.SetStopFrame(frame);
            state->phase = 2;
            state->timer.SetSchedulerValue(0);
            return;
        }
        case 0:
            state->cursor_animation.StopAtFrame1();
            state->background.StopAtFrame1();
            state->phase = 3;
            state->cursor.PopSelection();
            break;
        }
        state->timer.SetSchedulerValue(0);
        return;
    case 3:
        if (state->timer.field_04 < 12) break;
        state->phase = 0;
        switch (state->cursor.selection) {
        case 2:
            state->background.StopAtFrame1();
            data_00491fb8 = 10;
            return;
        case 1:
            state->cursor_animation.StopAtFrame1();
            state->background.StopAtFrame1();
            SetInputMode(&data_00491c28, 4);
            return;
        case 0:
            reinterpret_cast<PauseOwner_00422c30*>(state)->Unpause();
            break;
        }
    }
    return;
    escape:
        if (data_00474e36 & 8) {
            state->cursor.Select(0);
            state->cursor_animation.StopAtFrame1();
            state->background.StopAtFrame1();
            state->pause_animation.StopAtFrame1();
            state->phase = 3;
            state->timer.SetSchedulerValue(0);
            return;
        }


}
#pragma code_seg()

#include "../../../layout/ltcg/pause_choice_00422c80/child.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/find.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/input_mask.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/input_mode.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/mark6.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/menu.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/queue.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/registrar.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/setflag.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/setstop.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/stop1.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/timer.cpp"
#include "../../../layout/ltcg/pause_choice_00422c80/unpause.cpp"
