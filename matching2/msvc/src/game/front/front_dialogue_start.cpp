// 0x00415DB0: Front::StartDialogue — create the stage dialogue state at
// Front+0x9EB8 from the stage MSG table at Front+0x9EBC, and advance
// g_stage_progress. Native LTCG keeps the Front pointer in EDI and the stage
// index in ESI; the compiler-generated cleanup at 0x00465820 frees the block
// if the constructor throws.
#include "th10/game/item_score_display_create.hpp"

#pragma code_seg(".text$01b_create")
void FrontDialogueOwner::StartDialogue(int stage) {
    score_display = new FrontDialogueState(
        reinterpret_cast<char*>(score_table) + score_table[stage].offset);
    score_display->stage = stage;
    int next = stage + 1;
    int previous = g_stage_progress;
    g_stage_progress = next;
    if (previous != next)
        g_stage_progress_echo = 0;
}
#pragma code_seg()
