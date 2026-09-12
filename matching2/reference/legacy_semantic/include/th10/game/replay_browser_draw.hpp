#pragma once
struct ReplayBrowserDate{int year,month,day,hour,minute;};
struct ReplayBrowserRun{const char*name;long timestamp;float clear_percent;int character,shot,difficulty,stage,total_score,score_digit;};
struct ReplayBrowserScore{const char*label;bool available;int score,digit;};
struct ReplayBrowserSlot{const ReplayBrowserRun*run;ReplayBrowserScore rows[7];};
struct ReplayBrowser{int state,selection,timer;float transition;int chosen;const ReplayBrowserSlot*slots[25];};
struct ReplayBrowserDrawState{float x,y,z;unsigned color;int busy;};
struct ReplayBrowserEnv{ReplayBrowserDrawState*render;const char*const*shots;const char*const*difficulties;const char*const*stages;ReplayBrowserDate(*decode)(long);void(*draw)(const ReplayBrowserDrawState*,const char*);};
int ReplayBrowser_Draw(const ReplayBrowser*,const ReplayBrowserEnv*);
