#include "../../src/game/fps/stats_task.cpp"
#pragma code_seg(".text$02context")
extern "C" StatsDisplay* __cdecl StatsDisplayCompilerContext() { return StatsDisplay_Create(); }
#pragma code_seg()
