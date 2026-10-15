// Compiler context only; these bytes do not enter the recovered image.
#include "../../../src/game/laser/laser_manager_on_update.cpp"

// Synthetic entry: the primary scheduler task only ever reaches this callback
// with the object the score manager published at 0x0047781C, so the context
// materialises that global's link-time address and calls the modelled member.
extern "C" LaserManagerUpdateView g_laser_manager;

#pragma code_seg(".text$05context")
int __stdcall ScoreRecordsAdvanceFrameCompilerContext() {
    return g_laser_manager.AdvanceFrame();
}
#pragma code_seg()
