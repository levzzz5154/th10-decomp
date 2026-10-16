// E5: the executor TU calls MarkText three times, as in the real cluster.
#include "../../../src/game/background/player_set_scheduler_value.cpp"
#include "th10/game/recovery_script_executor_cluster/recovery_script_executor.hpp"

#pragma code_seg(".text$00401000_context")
extern "C" int __stdcall RecoveryScriptExecutorCompilerContext_0040bd80(
    RecoveryScriptState* script) {
    return RecoveryScript_Execute2(script);
}
#pragma code_seg()
