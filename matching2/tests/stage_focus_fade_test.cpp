#include "th10/game/stage_focus_fade.hpp"
#include <cstdio>
static int f,prep;
#define C(x) do{if(!(x)){++f;std::printf("FAIL %d\n",__LINE__);}}while(0)
static void P(StageFocusState*,void*,int x){prep=x;}
int main(){StageFocusEntity a={7,2,20,0,0,200},b={8,1,20,0,0,160};StageFocusNode nb={&b,0},na={&a,0};StageFocusState s={0,9,3,0,{}};s.slots[0]={7,224,16,0,40};s.slots[1]={8,270,16,0,40};s.slots[2].handle=99;StageFocusEnv e={4,0,0,&na,&nb,P};C(StageFocus_UpdateFade(&s,&e)==1);C(prep==1&&s.frame==1&&s.secondary_frame==1);C(a.alpha==50);C(b.alpha==138);C(s.slots[2].handle==0);a.suppress_focus_fade=1;a.alpha=77;StageFocus_UpdateFade(&s,&e);C(a.alpha==77);return f;}
