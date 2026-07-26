#pragma once
#include <cstdint>
struct ReplayRunSnapshot{int stage;short route;int score;short power;int lives,bombs,continues,graze;float gauge;unsigned flags;};
struct ReplayRuntimeGlobals{int stage,character,shot,difficulty;short route;int score;short power;int lives,bombs,continues,graze;float gauge;unsigned flags;};
struct ReplayRuntime{int mode;uint32_t magic;uint16_t version;uint32_t capacity;ReplayRunSnapshot snapshot;ReplayRunSnapshot stages[8];void*update_task;void*draw_task;void*aux_task;int active_stage;};
struct ReplayRuntimeOps{void*context;bool(*load)(void*,const char*,ReplayRuntime*);void*(*register_task)(void*,int priority,int kind,ReplayRuntime*);void(*copy_profile_out)(void*,ReplayRunSnapshot*);void(*copy_profile_in)(void*,const ReplayRunSnapshot*);};
// 0x00428F60: mode in EAX, path in ECX, owner in EBX.
int ReplayRuntime_Bootstrap(ReplayRuntime*,int mode,const char*path,ReplayRuntimeGlobals*,const ReplayRuntimeOps*);
