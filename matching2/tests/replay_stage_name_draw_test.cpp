#include "th10/game/replay_stage_name_draw.hpp"
#include <cstdio>
#include <cstring>
static int f,n;static char o[40][192];static ReplayScoreDrawState s[40];
#define C(x) do{if(!(x)){++f;std::printf("FAIL %d\n",__LINE__);}}while(0)
static ReplayScoreDate Dt(long){return{2026,7,26,5,19};}static void Dr(const ReplayScoreDrawState*x,const char*y){s[n]=*x;std::strcpy(o[n++],y);}int main(){ReplayScoreEntry q[10]={};for(int i=0;i<10;++i){q[i].name="E";q[i].stage=1;}q[0]={"R",1,0,2,1,50};const char*d[]={"Easy"};ReplayScoreDrawState rs={};ReplayStageNameEnv e={&rs,q,0,0,"ABCDEFGHIJKLMxyz",d,Dt,Dr};ReplayStageNamePage p={2,1,true,0,"ABC",8,2};ReplayStageName_Draw(&p,&e);C(n==10&&s[0].color==0xffffffffu&&s[9].color==0xff6f6fffu);n=0;p.fade_rows=false;ReplayStageName_Draw(&p,&e);C(n==10+2+16&&std::strcmp(o[10],"ABC")==0&&s[11].x==147);n=0;p.state=1;ReplayStageName_Draw(&p,&e);C(n==0);return f;}
