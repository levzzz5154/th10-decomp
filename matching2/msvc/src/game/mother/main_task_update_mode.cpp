// 0x004218D0: switch the main task to the mode requested in next_mode.
// Destroys what the previous mode owned, creates what the new one needs and
// returns 1; returns 4 once the application has to quit.
#include "th10/app/main_task_mode.hpp"
#include "th10/game/stage_startup_00417870.hpp"

inline StageRunState* GameState() { return &g_globals; }

#pragma code_seg(".text$00c_mode")
int MainTaskStateWave18::UpdateMode() {
    if (current_mode != next_mode) {
        imp_EnterCriticalSection(critical_sections[5]);
        int previous = current_mode;
        ++lock_depth[5];
        previous_mode = previous;
        overlay_color = 0xFF000000;
        switch (next_mode) {
        case 0:
            // Start-up: without the shared state the application quits.
            next_mode = 1;
            created_state = ModeCreateStateWave18();
            if (created_state) break;
            next_mode = 3;
            goto quit;
        case 4:
            // Start the game.
            switch (previous) {
            case 7:
                Game_Delete(g_game);
            case 1:
            case 2:
                ModeCreateProgressWave18();
                break;
            case 14:
                ScoreOwnedObject_Destroy(g_ending);
                ModeCreateProgressWave18();
                break;
            }
            break;
        case 15:
            // Start the game from its third entry point.
            switch (previous) {
            case 2:
                break;
            case 14:
                ScoreOwnedObject_Destroy(g_ending);
                break;
            case 7:
                Game_Delete(g_game);
                break;
            default:
                goto done;
            }
            next_mode = 4;
            g_main_mode_request = 3;
            ModeCreateProgressWave18();
            break;
        case 7:
            // Open the menu screen.
            if (previous == 4) Title_Delete(g_title);
            ui_mode = 1;
            ModeCreateUiWave18(0);
            break;
        case 12:
            if (previous == 4) Title_Delete(g_title);
            next_mode = 7;
            ui_mode = 1;
            ModeCreateUiWave18(1);
            break;
        case 11: {
            // Reopen the menu screen with the argument it had.
            unsigned int argument = reinterpret_cast<GameUiArgumentWave18*>(g_game)->argument;
            ui_mode = 0;
            if (previous == 7) Game_Delete(g_game);
            next_mode = 7;
            ModeCreateUiWave18(argument);
            break;
        }
        case 10:
            // Reopen the menu screen for the stage shown last.
            Game_Delete(g_game);
            ui_mode = 1;
            next_mode = 7;
            GameState()->stage = GameState()->stage_shown;
            g_stage_route_current = g_stage_routes + GameState()->stage_shown;
            ModeCreateUiWave18(0);
            break;
        case 13:
            Game_Delete(g_game);
            ui_mode = 1;
            next_mode = 7;
            ModeCreateUiWave18(0);
            break;
        case 14:
            // Open the result screen.
            if (previous == 7) Game_Delete(g_game);
            ModeCreateSmallWave18();
            break;
        case 3:
        quit:
            ModeReleaseGlobalsWave18();
            LeaveSlot(5);
            return 4;
        }
    done:
        current_mode = next_mode;
        imp_LeaveCriticalSection(critical_sections[5]);
        --lock_depth[5];
    }
    return 1;
}
#pragma code_seg()
