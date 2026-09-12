#pragma once
#include <cstdint>
struct ShotPracticeState{int phase,selection,previous_selection,selection_count,phase_timer;int unavailable[3],unavailable_count;};
struct ShotPracticeEnv{uint32_t held,pressed;int difficulty,character,shot;bool replay_mode;bool available[3];int stage,launch_state;};
struct ShotPracticeOps{void*context;void(*set_phase)(void*,int);void(*move_selection)(void*,ShotPracticeState*,int);void(*play_sound)(void*,int);void(*open_view)(void*,int);void(*close_view)(void*,int);void(*reset_selection)(void*);void(*start_fade)(void*,float,float);void(*launch)(void*,float);};
// 0x00430A60 - character shot/style selector.
int ShotPracticeMenu_Update(ShotPracticeState*,ShotPracticeEnv*,const ShotPracticeOps*);
