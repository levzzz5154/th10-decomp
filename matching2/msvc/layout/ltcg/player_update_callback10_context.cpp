// Real Update and scheduler callback only; no synthetic callers.
#include "player_update_callback10_dependencies/player_update_callback_context.cpp"
#include "../../src/unidentified/FUN_00405840_00405840.cpp"
// Actual secondary callback installed alongside the primary callback.
#pragma code_seg(".text$037secondary")
extern "C" __declspec(noinline) int __cdecl PlayerSecondaryCallback_00405850() {
    return 1;
}
#pragma code_seg()
