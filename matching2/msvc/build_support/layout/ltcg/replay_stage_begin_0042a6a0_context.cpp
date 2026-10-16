// Compiler context only; never selected as recovered game code.
#include "../../../src/game/replay/replay_stage_begin.cpp"

extern "C" int __cdecl ReplayStageBeginEscape(void* pointer, int value);

// A caller that keeps the manager live across calls and lets the addresses of
// the game state, the generator and the configuration word escape: they are
// parts of objects the rest of the program reaches through pointers.
#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall ReplayStageBeginContext(ReplayManager2** managers, int count) {
    int total = ReplayStageBeginEscape(&g_globals, 0) + ReplayStageBeginEscape(&g_rng, 1) +
                ReplayStageBeginEscape(&g_stage_flags, 2);
    for (int index = 0; index < count; ++index) {
        ReplayManager2* manager = managers[index];
        total += ReplayStageBeginEscape(manager, index);
        manager->BeginStage();
        total += ReplayStageBeginEscape(manager, total);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()
