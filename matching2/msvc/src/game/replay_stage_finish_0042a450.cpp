// 0x0042A450..0x0042A696: close the current stage in the replay manager.
//
// The manager's tasks are paused for the frame. While recording, the stage's
// input pages are restarted and the stage record takes the game counters
// (unless the configuration word is set), the boss gauge, the player's state
// block and the four values of each player option. During playback the same
// player state is put back from the record instead; with shot type 5 an
// option's fourth value restarts from its first.
//
// The manager arrives in EBX (the compiler's own convention).
#include "th10/game/replay_stage_finish_0042a450.hpp"

#pragma code_seg(".text$06finish")
void ReplayManager_0042a6a0::FinishStage() {
    if (update_task)
        update_task->flags |= 2;
    if (extra_task)
        extra_task->flags |= 2;
    if (draw_task)
        draw_task->flags |= 2;
    if (mode == 0) {
        ReplayStage_0042a6a0* record = stage_data[data_00474c40.stage];
        ReplayFinishClearPools_0042ab20(this, data_00474c40.stage);
        current_pool = AppendPage(data_00474c40.stage);
        if (data_00491fc4 == 0) {
            record->score = data_00474c40.score;
            record->word_10 = data_00474c40.word_08;
            record->gauge = data_00474c40.gauge;
            record->gauge_frame = data_00474c40.gauge_timer.current;
            record->field_1c = data_00474c40.field_30;
            record->field_20 = data_00474c40.field_58;
            record->continues = data_00474c40.continues;
        }
        Player_0042a450* player = data_00477834;
        record->boss_gauge = player->boss_gauge;
        memcpy(stage_data[data_00474c40.stage]->player_state, player->state, sizeof(player->state));
        for (int index = 0; index < 4; ++index) {
            for (int kind = 0; kind < 4; ++kind)
                record->options[kind][index] = player->options[index].values[kind];
        }
        record->field_1b8 = data_00474c40.field_5c;
        stage = data_00474c40.stage;
        stage_data[stage]->player_field_4474 = player->field_4474;
    } else if (mode == 1) {
        ReplayStage_0042a6a0* record = nodes[data_00474c40.stage].stage;
        Player_0042a450* player = data_00477834;
        stage = data_00474c40.stage;
        player->SetBossGauge(&record->boss_gauge);
        Player_0042a450* current = data_00477834;
        memcpy(player->state, record->player_state, sizeof(record->player_state));
        current->field_4474 = record->player_field_4474;
        PlayerRefresh_00426f70(current);
        player = data_00477834;
        for (int index = 0; index < 4; ++index) {
            player->options[index].values[0] = record->options[0][index];
            player->options[index].values[1] = record->options[1][index];
            player->options[index].values[2] = record->options[2][index];
            player->options[index].values[3] = record->options[3][index];
            if (data_00474c40.shot_type + data_00474c40.character * 3 == 5)
                player->options[index].values[3] = record->options[0][index];
        }
        for (int index = 0; index < 4; ++index)
            player->options[index].flag = 0;
        ReplayPauseReset_00424d90((PauseState_00424d90*)player);
    }
    field_1c8 = 0;
}
#pragma code_seg()
