#define data_00491c10 stage_replay_data_00491c10
#define data_0047770c stage_replay_data_0047770c
#define data_00474c40 stage_replay_data_00474c40
#define g_ascii_manager stage_replay_data_004776e0
#define data_00477704 stage_replay_data_00477704
#define g_player stage_replay_data_00477834
#define data_00477838 stage_replay_data_00477838
#define data_0047783c stage_replay_data_0047783c
#define data_00476f78 stage_replay_data_00476f78
#define data_00491fc4 stage_replay_data_00491fc4
#define data_00491fb8 stage_replay_data_00491fb8
#define data_00492590 stage_replay_data_00492590
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
        Player* player = g_player;
        record->player_position = player->fixed_position;
        memcpy(stage_data[data_00474c40.stage]->player_position_history, player->position_history,
               sizeof(player->position_history));
        for (int index = 0; index < 4; ++index) {
            for (int kind = 0; kind < 4; ++kind)
                record->options[kind][index] = player->options[index].Point(kind);
        }
        record->field_1b8 = data_00474c40.field_5c;
        stage = data_00474c40.stage;
        stage_data[stage]->player_focused = player->focused;
    } else if (mode == 1) {
        ReplayStage_0042a6a0* record = nodes[data_00474c40.stage].stage;
        Player* player = g_player;
        stage = data_00474c40.stage;
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
            if (data_00474c40.shot_type + data_00474c40.character * 3 == 5)
                player->options[index].focused_offset = record->options[0][index];
        }
        for (int index = 0; index < 4; ++index)
            player->options[index].reset_position = 0;
        ReplayPauseReset_00424d90((PauseState_00424d90*)player);
    }
    field_1c8 = 0;
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
