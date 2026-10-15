// Compiler context only; these bytes do not enter the recovered image.
#include "../../src/game/score_display_on_update.cpp"

// Synthetic entry: the primary scheduler task only ever reaches this callback
// with the object the score manager published at 0x0047781C, so the context
// materialises that global's link-time address and calls the modelled member.
extern "C" ScoreRecords_0041c480 g_laser_manager;

#pragma code_seg(".text$05context")
int __stdcall ScoreRecordsAdvanceFrameCompilerContext() {
    return g_laser_manager.AdvanceFrame();
}
#pragma code_seg()
