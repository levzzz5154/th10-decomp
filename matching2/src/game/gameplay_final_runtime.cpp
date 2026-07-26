#include "th10/game/gameplay_final_runtime.hpp"
#include <algorithm>
#include <cmath>
namespace th10::gameplay_final {
// Semantic reconstruction of retail 0x0041AFD0.
int UpdateItems(ItemPool&p,float px,float py,float speed,int difficulty){p.active=0;for(auto&i:p.items){if(!i.active)continue;++p.active;++i.timer;switch(i.state){case 1:i.x+=i.vx*speed;i.y+=i.vy*speed;i.vy=std::min(2.0f,i.vy+.03f*speed);if(i.y>480)i.active=false;break;case 2:i.x+=(px-i.x)*.1f*speed;i.y+=(py-i.y)*.1f*speed;if(std::fabs(i.x-px)<8&&std::fabs(i.y-py)<8){i.active=false;++p.collected;}break;case 3:i.vx*=.95f;i.vy*=.95f;i.x+=i.vx;i.y+=i.vy;break;case 4:i.z+=.05f*speed;if(i.z>=1)i.state=2;break;default:break;}if(difficulty>3&&i.type==5)i.vy-=.01f;}return p.active;}
// Semantic reconstruction of retail 0x00425730.
int UpdatePlayerState(PlayerRuntime&s,std::uint32_t in){++s.timer;if(s.invulnerable>0)--s.invulnerable;switch(s.state){case 0:s.y=48000-s.timer*8000/60;if(s.timer>=30){s.state=1;s.timer=0;s.invulnerable=120;}break;case 1:if((in&0x2)&&s.bombs>0){--s.bombs;s.state=2;s.timer=0;s.invulnerable=180;s.events.push_back(2);}if(in&0x100){s.state=3;s.timer=0;}break;case 2:if(s.timer>90){s.state=1;s.timer=0;}break;case 3:if(s.timer==1){--s.lives;s.bombs=2;s.power=std::max(0,s.power-16);s.events.push_back(3);}if(s.timer>120){s.state=0;s.timer=0;}break;case 4:s.events.push_back(4);break;}return 1;}
// Semantic reconstruction of retail 0x00426F70.
void UpdateAttachedEffects(AttachedEffects&s,int c){s.counter=c;s.events.clear();for(int i=0;i<4;++i){if(!s.handles[i])continue;if(c<100){s.states[i]|=0x4000000;s.events.push_back(0x100+i);}else{s.states[i]=1;s.events.push_back(0x200+i);}}static const int map[6][4]={{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15},{16,17,18,19},{20,21,22,23}};int k=std::clamp(s.shot+s.difficulty*3,0,5);for(int i=0;i<4;++i)if(s.handles[i])s.events.push_back(map[k][i]);}
}
