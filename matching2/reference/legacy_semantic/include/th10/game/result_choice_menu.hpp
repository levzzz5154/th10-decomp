#pragma once
#include <cstdint>
struct ResultChoiceState{int phase,timer,selection,previous_selection,selection_count;bool initialized;};
struct ResultChoiceInput{uint32_t held,pressed;};
struct ResultChoiceEnv{bool continue_used;int launch_state;};
struct ResultChoiceOps{void*context;void(*set_animation)(void*,int);void(*move_selection)(void*,ResultChoiceState*,int);void(*play_sound)(void*,int);void(*reset_timer)(void*);void(*open_effect)(void*,int);void(*close_effect)(void*,int);void(*execute_choice)(void*,int,ResultChoiceEnv*);};
// 0x00422C80: menu object is the sole stack argument; caller register values
// are scratch inputs to register-bound callees, not function parameters.
int ResultChoiceMenu_Update(ResultChoiceState*,const ResultChoiceInput*,ResultChoiceEnv*,const ResultChoiceOps*);
