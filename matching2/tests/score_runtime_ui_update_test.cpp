#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

#include "th10/game/score_runtime_ui_update.hpp"

namespace {
struct Call { int slot, value; };
std::vector<Call> modes, scripts;
std::vector<int> ticks, panels;
float camera[3];
void Panel(void*, int p) { panels.push_back(p); }
void Mode(void*, int s, int v) { modes.push_back({s,v}); }
void Script(void*, int s, int v) { scripts.push_back({s,v}); }
void Tick(void*, int s) { ticks.push_back(s); }
void Camera(void*, const float p[3]) { std::memcpy(camera,p,sizeof(camera)); }
ScoreRuntimeUiOps Ops(){return {0,Panel,Mode,Script,Tick,Camera};}
void Clear(){modes.clear();scripts.clear();ticks.clear();panels.clear();std::memset(camera,0,sizeof(camera));}
ScoreRuntimeUiState State(){static float scale=1.0f; ScoreRuntimeUiState s={}; s.flags=1; s.frame_scale=&scale; return s;}
}
int main(){ScoreRuntimeUiOps ops=Ops(); float player[3]={100,200,-20}; uint32_t release=3; ScoreRuntimeUiEnv e={&release,80,123,7,player};
 {Clear(); auto s=State(); s.flags=0; assert(ScoreRuntimeUi_Update(&s,&e,&ops)==1); assert(scripts.empty());}
 {Clear(); auto s=State(); s.flags=1|2; s.frame=119; s.frame_accumulator=119; s.displayed_score=12345678; ScoreRuntimeUi_Update(&s,&e,&ops); assert((s.flags&4)!=0); assert((panels==std::vector<int>{0,1})); assert(modes.size()==3&&modes[0].value==3); for(int i=0;i<8;++i) assert(s.stage_modes[i]==3); assert(scripts[0].slot==0&&scripts[0].value==31); assert(scripts[7].value==38); assert(scripts[8].slot==9&&scripts[8].value==39); assert(scripts[9].value==39); assert(scripts[10].value==30&&scripts[11].value==37); assert(ticks.size()==13); assert(std::fabs(camera[0]-5.0f)<1e-6f);}
 {Clear(); auto s=State(); s.flags=1|4; s.frame=120; ScoreRuntimeUiEnv wide=e; wide.playfield_x=129; ScoreRuntimeUi_Update(&s,&wide,&ops); assert((s.flags&4)==0&&modes[0].value==2); assert(scripts[0].slot==8&&scripts[0].value==41);}
 {Clear(); auto s=State(); s.flags=1; s.frame=300; s.frame_accumulator=300; s.displayed_score=1000; s.target_score=1000; s.score_decay_end_frame=400; ScoreRuntimeUi_Update(&s,&e,&ops); assert(s.displayed_score==990); assert((release&1u)==0);}
 std::puts("SCORE_RUNTIME_UI_UPDATE_TESTS_PASS");}
