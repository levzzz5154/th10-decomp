// 0x00415DB0: build the score display of a stage from the score table and
// make the following stage the next one to play, restarting its progress if
// that changes. Native LTCG keeps the manager in EDI and the stage in ESI;
// the compiler-generated cleanup at 0x00465820 frees the block if the
// display's constructor throws.
#include "th10/game/item_score_display_create_00415db0.hpp"

#pragma code_seg(".text$01b_create")
void ItemManager_00415db0::CreateScoreDisplay(int stage) {
    score_display = new ItemScoreDisplay_00415db0(
        reinterpret_cast<char*>(score_table) + score_table[stage].offset);
    score_display->stage = stage;
    int next = stage + 1;
    int previous = g_stage_progress;
    g_stage_progress = next;
    if (previous != next)
        g_stage_progress_echo = 0;
}
#pragma code_seg()
