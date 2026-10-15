// Compiler context only; never selected as recovered game code.
//
// The ending/credits script interpreter is a whole-program-compiled frame:
// retail co-optimizes it with its timer, lookup, text, animation and music
// helpers, so the executor is compiled inside a native LTCG cluster rooted at
// this synthetic context. The context invokes the executor with its ordinary
// stack argument; every helper body is provided by the cluster's anchor TUs.
#include "recovery_script_executor_cluster/recovery_script_executor_0040bd80.cpp"

#pragma code_seg(".text$00401000_context")
extern "C" int __stdcall RecoveryScriptExecutorCompilerContext_0040bd80(
    RecoveryScriptState* script) {
    return RecoveryScript_Execute_0040bd80(script);
}
#pragma code_seg()
