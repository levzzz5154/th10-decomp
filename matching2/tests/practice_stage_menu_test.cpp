#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#include "th10/game/practice_stage_menu.hpp"

namespace {
std::vector<int> opened, closed, sounds;
int phases, resets, moves, fades, launches;
void Reset(void*) { ++resets; }
void Open(void*, int n) { opened.push_back(n); }
void Close(void*, int n) { closed.push_back(n); }
void Phase(void*, int n) { phases = n; }
void Move(void*, PracticeStageMenuState* s, int d) {
    ++moves; s->selection = (s->selection + d + s->selection_count) % s->selection_count;
}
void Sound(void*, int n) { sounds.push_back(n); }
void Fade(void*, float w, float h) { assert(w == 480.0f && h == 384.0f); ++fades; }
void Launch(void*, float stage) { assert(stage == 6.0f); ++launches; }
PracticeStageMenuOps Ops() { return {0,Reset,Open,Close,Phase,Move,Sound,Fade,Launch}; }
void Clear() { opened.clear(); closed.clear(); sounds.clear(); phases=resets=moves=fades=launches=0; }
PracticeStageMenuEnv Env() { static uint8_t u[6]={1,0,1,1,1,1}; static int8_t a[9]={0},b[9]={0}; return {0,0,2,1,0,0,u,a,b,true,0,0,0,0}; }
}
int main() {
    PracticeStageMenuOps ops=Ops();
    { Clear(); auto e=Env(); PracticeStageMenuState s={0,0,0,0,11}; PracticeStageMenu_Update(&s,&e,&ops); assert(s.selection_count==6&&s.selection==2); assert((opened==std::vector<int>{106,108})); assert(phases==2); }
    { Clear(); auto e=Env(); PracticeStageMenuState s={2,0,0,6,0}; e.pressed=0x20; PracticeStageMenu_Update(&s,&e,&ops); assert(s.selection==1&&moves==1&&sounds.back()==12); }
    { Clear(); auto e=Env(); PracticeStageMenuState s={2,1,0,6,0}; e.pressed=0x1001; const_cast<int8_t*>(e.fallback_keys)[4]=-1; e.direct_poll_succeeded=false; PracticeStageMenu_Update(&s,&e,&ops); assert(sounds.back()==37&&e.shortcut_stage==5&&e.remembered_selection==1); }
    { Clear(); auto e=Env(); PracticeStageMenuState s={3,4,0,6,10}; PracticeStageMenu_Update(&s,&e,&ops); assert(fades==1&&sounds.back()==43); s.phase_timer=40; PracticeStageMenu_Update(&s,&e,&ops); assert(e.selected_stage==5&&e.game_mode==5&&e.launch_state==7&&launches==1); }
    { Clear(); auto e=Env(); PracticeStageMenuState s={4,0,0,6,6}; PracticeStageMenu_Update(&s,&e,&ops); assert(resets==1&&phases==8); assert((closed==std::vector<int>{106,108})); }
    std::puts("PRACTICE_STAGE_MENU_TESTS_PASS");
}
