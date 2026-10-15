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
#include "th10/game/stage_startup_00417870.hpp"

#pragma code_seg(".text$0042a6a0_fn")
void ReplayManager_0042a6a0::BeginStage() {
    if (mode == 0) {
        stage_data[g_globals.stage] = new ReplayStage_0042a6a0;
        ReplayStage_0042a6a0* stage = stage_data[g_globals.stage];
        stage->seed = g_rng.seed;
        g_rng.generation = 0;
        stage->stage = (short)g_globals.stage;
        stage->flag = g_application.stage_reset;
    } else if (mode == 1) {
        ReplayNode_0042a6a0* node = &nodes[g_globals.stage];
        node->cursor = node->inputs;
        node->cursor_end = node->inputs_end;
        node->count = 0;
        ReplayStage_0042a6a0* stage = node->stage;
        g_rng.seed = stage->seed;
        g_rng.generation = 0;
        g_globals.score = stage->score;
        g_globals.word_08 = stage->word_10;
        g_globals.SetGauge(stage->gauge * 10);
        g_globals.gauge_timer.Set(stage->gauge_frame);
        g_globals.lives = stage->field_1c;
        g_globals.field_58 = stage->field_20;
        g_globals.continues = stage->continues;
        g_globals.field_5c = nodes[g_globals.stage].stage->field_1b8;
    }
}
#pragma code_seg()
