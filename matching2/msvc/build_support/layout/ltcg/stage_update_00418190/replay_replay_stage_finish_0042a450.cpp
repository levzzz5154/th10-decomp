#define g_sprt_ctrl stage_replay_g_sprt_ctrl
#define g_front stage_replay_g_front
#define g_globals stage_replay_data_00474c40
#define g_ascii_manager stage_replay_data_004776e0
#define g_enemy_ctrl stage_replay_g_enemy_ctrl
#define g_player stage_replay_data_00477834
#define g_replay stage_replay_data_00477838
#define g_score stage_replay_data_0047783c
#define g_game_speed stage_replay_data_00476f78
#define g_stage_flags stage_replay_data_00491fc4
#define g_main_state stage_replay_data_00491fb8
#define g_sound_manager stage_replay_data_00492590
// 0x0042A450..0x0042A696: close the current stage in the replay manager.
//
// The manager's tasks are paused for the frame. While recording, the stage's
// input pages are restarted and the stage record takes the game counters
// (unless the configuration word is set), the player's fixed-point position and
// position history, its focus flag and the four points of each option. During playback the same
// player state is put back from the record instead; with shot type 5 an
// option's fourth value restarts from its first.
//
// The manager arrives in EBX (the compiler's own convention).
#include "th10/game/replay_stage_finish_0042a450.hpp"

#pragma code_seg(".text$0042a450_fn")
void ReplayManager_0042a6a0::FinishStage() {
    if (update_task)
        update_task->flags |= 2;
    if (extra_task)
        extra_task->flags |= 2;
    if (draw_task)
        draw_task->flags |= 2;
    if (mode == 0) {
        ReplayStage_0042a6a0* record = stage_data[g_globals.stage];
        ReplayFinishClearPools_0042ab20(this, g_globals.stage);
        current_pool = AppendPage(g_globals.stage);
        if (g_stage_flags == 0) {
            record->score = g_globals.score;
            record->word_10 = g_globals.word_08;
            record->gauge = g_globals.gauge;
            record->gauge_frame = g_globals.gauge_timer.current;
            record->field_1c = g_globals.field_30;
            record->field_20 = g_globals.field_58;
            record->continues = g_globals.continues;
        }
        Player* player = g_player;
        record->player_position = player->fixed_position;
        memcpy(stage_data[g_globals.stage]->player_position_history, player->position_history,
               sizeof(player->position_history));
        for (int index = 0; index < 4; ++index) {
            for (int kind = 0; kind < 4; ++kind)
                record->options[kind][index] = player->options[index].Point(kind);
        }
        record->field_1b8 = g_globals.field_5c;
        stage = g_globals.stage;
        stage_data[stage]->player_focused = player->focused;
    } else if (mode == 1) {
        ReplayStage_0042a6a0* record = nodes[g_globals.stage].stage;
        Player* player = g_player;
        stage = g_globals.stage;
        player->SetFixedPosition(&record->player_position);
        Player* current = g_player;
        memcpy(player->position_history, record->player_position_history,
               sizeof(record->player_position_history));
        current->focused = record->player_focused;
        PlayerRefresh_00426f70(current);
        player = g_player;
        for (int index = 0; index < 4; ++index) {
            player->options[index].target = record->options[0][index];
            player->options[index].position = record->options[1][index];
            player->options[index].unfocused_offset = record->options[2][index];
            player->options[index].focused_offset = record->options[3][index];
            if (g_globals.shot_type + g_globals.character * 3 == 5)
                player->options[index].focused_offset = record->options[0][index];
        }
        for (int index = 0; index < 4; ++index)
            player->options[index].reset_position = 0;
        ReplayPauseReset_00424d90((PauseState_00424d90*)player);
    }
    field_1c8 = 0;
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager
