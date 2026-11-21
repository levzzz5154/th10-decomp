// E5: the executor TU calls MarkText three times, as in the real cluster.
#include "../../../src/game/background/frame_timer_set.cpp"
#include "th10/game/ending_script_cluster/script_executor.hpp"

#pragma code_seg(".text$00401000_context")
extern "C" int __stdcall RecoveryScriptExecutorCompilerContext_0040bd80(
    EndingScriptState* script) {
    return EndingScript_Execute(script);
}
#pragma code_seg()
