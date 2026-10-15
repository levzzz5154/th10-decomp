#define SCRIPT_WORKER_EXPORTED_ABI
#pragma code_seg(".text$16worker")
#include "../../src/game/title/title_destroy.cpp"
#pragma code_seg()
#pragma code_seg(".text$02context")
extern "C" void __stdcall DestroyScriptStateContext(Title* state) { state->~Title(); }
#pragma code_seg()
