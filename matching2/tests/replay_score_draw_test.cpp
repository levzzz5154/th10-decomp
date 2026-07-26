#include "th10/game/replay_score_draw.hpp"
#include <cstdio>
#include <cstring>
static int fail,n;static char text[20][192];static ReplayScoreDrawState seen[20];
#define C(x) do{if(!(x)){std::printf("FAIL %d %s\n",__LINE__,#x);++fail;}}while(0)
static ReplayScoreDate Date(long){return {2026,7,26,5,9};}static void Draw(const ReplayScoreDrawState*s,const char*t){seen[n]=*s;std::strcpy(text[n++],t);}
int main(){ReplayScoreEntry q[20]={};for(int i=0;i<20;++i){q[i].name="EMPTY";q[i].score=i;q[i].stage=3;}q[10]={"R1",12345,1,4,1,87.5f};int ss0[2]={7,8},ss1[2]={9,10};ReplayScoreData d={q,{1,222,3,4},{0,3661,0,0},{ss0,ss1,ss0,ss0}};const char* labs[]={"Easy","Normal"};ReplayScoreDrawState st={};ReplayScoreDrawEnv e={&st,&d,labs,Date,Draw};ReplayScorePage p={2,1,1,0};C(ReplayScore_Draw(&p,&e)==1);C(n==13);C(std::strstr(text[0],"R1      123454  2026/07/26 05:09  Normal  87.5%")!=0);C(seen[0].color==0xffffffffu&&seen[9].color==0xff6f6fffu);C(seen[0].y==160&&seen[9].y==295);C(std::strcmp(text[11],"  1:01:01")==0);C(std::strcmp(text[12],"       10")==0);C(st.busy==0&&st.y==414);
n=0;p.suppress_entries=1;ReplayScore_Draw(&p,&e);C(n==3&&seen[0].y==378);n=0;p.state=1;st.busy=7;ReplayScore_Draw(&p,&e);C(n==0&&st.busy==7);return fail;}
