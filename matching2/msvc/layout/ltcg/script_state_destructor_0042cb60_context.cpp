#define SCRIPT_WORKER_EXPORTED_ABI
#pragma code_seg(".text$16worker")
#include "../../src/game/title/script_state_destructor_0042cb60.cpp"
#pragma code_seg()
#pragma code_seg(".text$02context")
extern "C" void __stdcall DestroyScriptStateContext(ScriptState_0042cb60* state) { state->~ScriptState_0042cb60(); }
#pragma code_seg()
