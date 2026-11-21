// 0x004218D0: switch the main task to the mode requested in next_mode.
// Destroys what the previous mode owned, creates what the new one needs and
// returns 1; returns 4 once the application has to quit.
#include "th10/app/main_task_mode.hpp"
#include "th10/game/stage_startup.hpp"

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
        case MAIN_MODE_BOOT:
            // Start-up: create the loading/bootstrap task (0x0041FD00); quit on failure.
            next_mode = MAIN_MODE_LOADING;
            created_state = ModeCreateStateWave18();
            if (created_state) break;
            next_mode = MAIN_MODE_QUIT;
            goto quit;
        case MAIN_MODE_TITLE:
            // Open the title / main menu screen (Title_Create at 0x0042CD50).
            switch (previous) {
            case MAIN_MODE_GAME:
                Game_Delete(g_game);
            case MAIN_MODE_LOADING:
            case MAIN_MODE_INIT_DONE:
                ModeCreateProgressWave18();
                break;
            case MAIN_MODE_ENDING:
                ScoreOwnedObject_Destroy(g_ending);
                ModeCreateProgressWave18();
                break;
            }
            break;
        case MAIN_MODE_TITLE_RETURN:
            // Return to the title screen with request 3 (e.g. replay save / post-run).
            switch (previous) {
            case MAIN_MODE_INIT_DONE:
                break;
            case MAIN_MODE_ENDING:
                ScoreOwnedObject_Destroy(g_ending);
                break;
            case MAIN_MODE_GAME:
                Game_Delete(g_game);
                break;
            default:
                goto done;
            }
            next_mode = MAIN_MODE_TITLE;
            g_main_mode_request = 3;
            ModeCreateProgressWave18();
            break;
        case MAIN_MODE_GAME:
            // Start normal gameplay (Game_Create(0) at 0x004180E0).
            if (previous == MAIN_MODE_TITLE) Title_Delete(g_title);
            ui_mode = 1;
            ModeCreateUiWave18(0);
            break;
        case MAIN_MODE_GAME_REPLAY:
            // Start replay playback (Game_Create(1)).
            if (previous == MAIN_MODE_TITLE) Title_Delete(g_title);
            next_mode = MAIN_MODE_GAME;
            ui_mode = 1;
            ModeCreateUiWave18(1);
            break;
        case MAIN_MODE_GAME_RESTART: {
            // Restart gameplay preserving the replay_mode argument.
            unsigned int argument = reinterpret_cast<GameUiArgumentWave18*>(g_game)->argument;
            ui_mode = 0;
            if (previous == MAIN_MODE_GAME) Game_Delete(g_game);
            next_mode = MAIN_MODE_GAME;
            ModeCreateUiWave18(argument);
            break;
        }
        case MAIN_MODE_GAME_NEXT_STAGE:
            // Advance to stage_shown and start gameplay for that stage.
            Game_Delete(g_game);
            ui_mode = 1;
            next_mode = MAIN_MODE_GAME;
            GameState()->stage = GameState()->stage_shown;
            g_stage_route_current = g_stage_routes + GameState()->stage_shown;
            ModeCreateUiWave18(0);
            break;
        case MAIN_MODE_GAME_RELOAD:
            // Tear down and recreate gameplay for the current stage.
            Game_Delete(g_game);
            ui_mode = 1;
            next_mode = MAIN_MODE_GAME;
            ModeCreateUiWave18(0);
            break;
        case MAIN_MODE_ENDING:
            // Open the ending / staffroll screen (0x0040B940).
            if (previous == MAIN_MODE_GAME) Game_Delete(g_game);
            ModeCreateSmallWave18();
            break;
        case MAIN_MODE_QUIT:
        quit:
            ModeReleaseGlobalsWave18();
            LeaveSlot(5);
            return MAIN_TASK_QUIT;
        }
    done:
        current_mode = next_mode;
        imp_LeaveCriticalSection(critical_sections[5]);
        --lock_depth[5];
    }
    return MAIN_TASK_CONTINUE;
}
#pragma code_seg()
