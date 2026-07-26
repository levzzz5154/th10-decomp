#include "th10/game/player_front_runtime.hpp"
#include <algorithm>
namespace th10::player_front {
// Semantic reconstruction of register-bound retail 0x004250B0 (player in EDI).
void UpdatePlayer(Player&p,std::uint32_t in,bool enabled,int speed,int slow,const PlayerEdges&e){int old=p.direction;bool l=in&0x10,r=in&0x20,u=in&0x40,d=in&0x80;p.direction=l?(u?5:d?7:1):r?(u?6:d?8:2):u?3:d?4:0;p.slow=enabled&&bool(in&4);int v=p.slow?slow:speed;p.vx=(l?-v:r?v:0);p.vy=(u?-v:d?v:0);if((old<0)!=(p.vy<0)||(old>0)!=(p.vy>0))if(e.direction_changed)e.direction_changed(e.context);p.slow_age=p.slow?0:std::min(30,p.slow_age+1);p.x=std::clamp(p.x+p.vx,-0x47e0,0x47e0);p.y=std::clamp(p.y+p.vy,0xc80,0xa8c0);if(e.random){p.x=std::clamp(p.x+e.random(e.context),-0x47e0,0x47e0);p.y=std::clamp(p.y+e.random(e.context),0xc80,0xa8c0);}if(!p.slow&&(p.vx||p.vy)){for(int i=31;i>0;--i)p.trail[i]=p.trail[i-1];}p.trail[0]={p.x,p.y};}
// Semantic reconstruction of retail 0x00413BC0.
void InitializeFront(Front&f,const FrontInput&i){f.update_task=f.draw_task=true;for(int n=0;n<9;++n)f.lives[n]=n<i.lives;int q=((i.counter%20)*100)/20;f.digits={i.counter/20+8,q/10+8,q%10+8};f.animations.clear();if(i.mode!=8){if(!i.special){f.animations.push_back(0);f.animations.push_back(1);}f.animations.push_back(0x71);}if(i.stage_one_clear)f.animations.push_back(0x4f);if(i.extra_overlay)f.animations.push_back(i.difficulty+0x66);f.animations.push_back(i.difficulty+0x6b);f.linked_a=f.animations.size()>1?f.animations[f.animations.size()-2]:0;f.linked_b=f.animations.back();}
}
