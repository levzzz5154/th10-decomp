// 0x0042A6A0..0x0042A804: start the current stage in the replay manager.
//
// While recording, a zeroed stage record is allocated and takes the stage
// number, the generator seed and the configuration's low bit. During playback
// the stage's input list is rewound and the saved seed, score, gauge, gauge
// timer and counters are put back into the game state. Either way the
// generator's word count restarts.
//
// The manager arrives in EBX (the compiler's own convention for the single
// call in the stage entry).
#include "th10/game/replay_stage_begin_0042a6a0.hpp"

#pragma code_seg(".text$0042a6a0_fn")
void ReplayManager_0042a6a0::BeginStage() {
    if (mode == 0) {
        stage_data[data_00474c40.stage] = new ReplayStage_0042a6a0;
        ReplayStage_0042a6a0* stage = stage_data[data_00474c40.stage];
        stage->seed = data_004918b0.seed;
        data_004918b0.generation = 0;
        stage->stage = (short)data_00474c40.stage;
        stage->flag = data_00491fc4;
    } else if (mode == 1) {
        ReplayNode_0042a6a0* node = &nodes[data_00474c40.stage];
        node->cursor = node->inputs;
        node->cursor_end = node->inputs_end;
        node->count = 0;
        ReplayStage_0042a6a0* stage = node->stage;
        data_004918b0.seed = stage->seed;
        data_004918b0.generation = 0;
        data_00474c40.score = stage->score;
        data_00474c40.word_08 = stage->word_10;
        data_00474c40.SetGauge(stage->gauge * 10);
        data_00474c40.gauge_timer.Set(stage->gauge_frame);
        data_00474c40.field_30 = stage->field_1c;
        data_00474c40.field_58 = stage->field_20;
        data_00474c40.continues = stage->continues;
        data_00474c40.field_5c = nodes[data_00474c40.stage].stage->field_1b8;
    }
}
#pragma code_seg()
