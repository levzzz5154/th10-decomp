// Compiler context only: this caller is not a recovered application function.
// E3: replicates the real cluster's context — Set/Advance loop plus executor.
#include "../../../src/game/background/frame_timer_set.cpp"
#include "recovery_script_executor_cluster/recovery_script_executor.cpp"

#pragma code_seg(".text$00401000_context")
extern "C" int __stdcall SetProbeCompilerContext(
    EndingScriptState* script,
    GameFrameTimer* timers, int count, int value) {
    for (int index = 0; index < count; ++index) {
        timers[index].Set(value + index);
        timers[index].Advance(1.0f);
    }
    return EndingScript_Execute(script);
}
#pragma code_seg()
