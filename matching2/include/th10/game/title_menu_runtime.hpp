#pragma once
#include <cstdint>
struct TitleMenuClock{int previous,frame;float elapsed;const float*scale;};
struct DemoReplayInfo{int stage,character,shot,difficulty;};
struct TitleMenuRuntime{int phase,selection,selection_count;unsigned*owner_flags;TitleMenuClock clock;};
struct TitleMenuGlobals{int attract_mode,demo_counter,demo_index,input_mask;unsigned game_flags;int stage,character,shot,difficulty,previous_difficulty,launch_state;const char*demo_names[4];};
struct TitleMenuOps{void*context;bool(*load_demo)(void*,const char*,DemoReplayInfo*);void(*hide_title_vm)(void*,int);void(*reset_stage_ui)(void*);void(*play_title_music)(void*);void(*set_phase)(void*,int);void(*reset_selection)(void*);void(*open_view)(void*,int);void(*close_view)(void*,int);void(*dispatch_phase)(void*,int,TitleMenuRuntime*);};
// 0x0042CDF0; EAX is the sole menu pointer at entry (the wrapper is a tail jump).
int TitleMenuRuntime_Update(TitleMenuRuntime*,TitleMenuGlobals*,const TitleMenuOps*);
