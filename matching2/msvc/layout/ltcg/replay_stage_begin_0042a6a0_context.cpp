// Compiler context only; never selected as recovered game code.
#include "../../src/game/replay_stage_begin_0042a6a0.cpp"

extern "C" int __cdecl ReplayStageBeginEscape(void* pointer, int value);

// A caller that keeps the manager live across calls and lets the addresses of
// the game state, the generator and the configuration word escape: they are
// parts of objects the rest of the program reaches through pointers.
#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall ReplayStageBeginContext(ReplayManager_0042a6a0** managers, int count) {
    int total = ReplayStageBeginEscape(&data_00474c40, 0) + ReplayStageBeginEscape(&data_004918b0, 1) +
                ReplayStageBeginEscape(&data_00491fc4, 2);
    for (int index = 0; index < count; ++index) {
        ReplayManager_0042a6a0* manager = managers[index];
        total += ReplayStageBeginEscape(manager, index);
        manager->BeginStage();
        total += ReplayStageBeginEscape(manager, total);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()
