#include "th10/game/replay_browser_draw.hpp"
#include <cstdarg>
#include <cstdio>
namespace{void D(const ReplayBrowserEnv*e,const char*f,...){char b[192];va_list a;va_start(a,f);std::vsnprintf(b,sizeof b,f,a);va_end(a);e->draw(e->render,b);}void Run(const ReplayBrowserEnv*e,int n,const ReplayBrowserRun&r){auto d=e->decode(r.timestamp);D(e,"No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%",n,r.name,d.year%100,d.month,d.day,d.hour,d.minute,e->shots[r.character*3+r.shot],e->difficulties[r.difficulty],e->stages[r.stage],(double)r.clear_percent);}}
// 0x00431BA0 - Semantic reconstruction of replay browser list/detail drawing.
int ReplayBrowser_Draw(const ReplayBrowser*m,const ReplayBrowserEnv*e){auto&r=*e->render;if(m->state==2){r={58,80,0,r.color,1};for(int i=0;i<25;++i){r.color=i==m->selection?0xffffff00u:0xff808080u;if(m->slots[i]&&m->slots[i]->run)Run(e,i+1,*m->slots[i]->run);else D(e,"No.%.2d -------- --/--/-- --:-- ------- ------- --- ---%%",i+1);r.y+=15;}}
 else if(m->state==4){const ReplayBrowserSlot&s=*m->slots[m->chosen];r={80,80,0,r.color,1};if(m->timer<10)r.y=(10.0f-m->transition)*(m->chosen*15.0f-160.0f)*.1f+80.0f;Run(e,m->chosen+1,*s.run);if(m->timer>=10){r.x=220;r.y=128;for(int i=0;i<7;++i){r.color=i==m->selection?0xffffff00u:0xff808080u;const auto&q=s.rows[i];if(!q.available)D(e,"%s  ---------",q.label);else D(e,"%s  %.8d%d",q.label,q.score,q.digit);r.y+=18;}}} else { return 1; }
 r.color=0xffffffffu;r.busy=0;return 1;}
