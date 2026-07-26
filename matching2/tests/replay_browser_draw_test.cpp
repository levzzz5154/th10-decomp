#include "th10/game/replay_browser_draw.hpp"
#include <cstdio>
#include <cstring>
static int f,n;static char out[40][192];static ReplayBrowserDrawState seen[40];
#define C(x) do{if(!(x)){++f;std::printf("FAIL %d\n",__LINE__);}}while(0)
static ReplayBrowserDate Dt(long){return{2026,7,26,5,19};}static void Dr(const ReplayBrowserDrawState*s,const char*x){seen[n]=*s;std::strcpy(out[n++],x);}int main(){const char*sh[]={"A","B","C"},*di[]={"Easy"},*st[]={"S0"};ReplayBrowserRun run={"REP",1,75,0,1,0,0,0,0};ReplayBrowserSlot slot={&run,{}};for(int i=0;i<7;++i){slot.rows[i]={"Row",i!=2,100+i,i};}ReplayBrowser m={2,1,10,0,0,{}};m.slots[1]=&slot;ReplayBrowserDrawState rs={};ReplayBrowserEnv e={&rs,sh,di,st,Dt,Dr};ReplayBrowser_Draw(&m,&e);C(n==25&&seen[1].color==0xffffff00u&&rs.busy==0);n=0;m.state=4;m.chosen=1;m.selection=2;ReplayBrowser_Draw(&m,&e);C(n==8&&std::strcmp(out[3],"Row  ---------")==0&&seen[3].color==0xffffff00u);n=0;m.state=1;ReplayBrowser_Draw(&m,&e);C(n==0);return f;}
