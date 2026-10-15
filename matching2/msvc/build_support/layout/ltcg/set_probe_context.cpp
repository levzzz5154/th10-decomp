// Compiler context only: this caller is not a recovered application function.
// E3: replicates the real cluster's context — Set/Advance loop plus executor.
#include "../../../src/game/background/player_set_scheduler_value_00405410.cpp"
#include "recovery_script_executor_cluster/recovery_script_executor_0040bd80.cpp"

#pragma code_seg(".text$00401000_context")
extern "C" int __stdcall SetProbeCompilerContext(
    RecoveryScriptState* script,
    RecoveryTimer_0040bd80* timers, int count, int value) {
    for (int index = 0; index < count; ++index) {
        timers[index].Set(value + index);
        timers[index].Advance(1.0f);
    }
    return RecoveryScript_Execute_0040bd80(script);
}
#pragma code_seg()
