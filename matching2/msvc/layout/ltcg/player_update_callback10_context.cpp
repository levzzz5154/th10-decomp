// Scheduler callback only; Update is compiled from its own source.
#include "../../src/game/bomb_on_update.cpp"
// Actual secondary callback installed alongside the primary callback.
#pragma code_seg(".text$037secondary")
extern "C" __declspec(noinline) int __cdecl PlayerSecondaryCallback_00405850() {
    return 1;
}
#pragma code_seg()
