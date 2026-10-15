// Synthetic compiler context for the internal score cleanup ABI.
#include "../../contexts/legacy/game/score_cleanup.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall ScoreCleanupContext_0041c850(
        ScoreCleanupOwner_0041c850** owners, int count) {
    int total = 0;
    while (count-- > 0)
        total += (*owners++)->Cleanup(1);
    return total;
}
#pragma code_seg()
