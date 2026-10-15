// Compiler context only; never selected as recovered game code.
#include "../../src/game/replay_stage_finish_0042a450.cpp"

extern "C" int __cdecl ReplayStageFinishEscape(void* pointer, int value);

// A caller that keeps the manager live across calls and lets the addresses of
// the game state, the generator, the configuration word and the player pointer
// escape.
#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall ReplayStageFinishContext(ReplayManager_0042a6a0** managers, int count) {
    int total = ReplayStageFinishEscape(&data_00474c40, 0) + ReplayStageFinishEscape(&data_004918b0, 1) +
                ReplayStageFinishEscape(&data_00491fc4, 2) + ReplayStageFinishEscape(&g_player, 3);
    for (int index = 0; index < count; ++index) {
        ReplayManager_0042a6a0* manager = managers[index];
        total += ReplayStageFinishEscape(manager, index);
        manager->FinishStage();
        total += ReplayStageFinishEscape(manager, total);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()
