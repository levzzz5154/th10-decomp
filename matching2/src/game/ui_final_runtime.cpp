#include "th10/game/ui_final_runtime.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
namespace th10::ui_final {
// Semantic reconstruction of retail 0x00409280.
void QueueNotice(Notice&n,int slot,const std::string&text,int value,int difficulty,int stage){n.slot=slot;n.text=text;n.value=value;n.count=std::min(99999,n.count+1);for(int i=0;i<8;++i)n.animations[i]=i+1;n.animations[0]=difficulty+0x20;n.animations[1]=stage+0x30;}
// Semantic reconstruction of retail 0x00414900.
int UpdateFront(FrontTick&s){++s.timer;s.events.clear();for(int i=0;i<9;++i)s.events.push_back(0x100+i);for(int i=0;i<4;++i)s.events.push_back(0x120+i);for(int i=0;i<2;++i)s.events.push_back(0x130+i);if(s.boss_active)s.events.push_back(0x140);if(!s.player_visible)s.events.push_back(0x141);if(s.transition&&s.timer>120)s.mode=14;return 1;}
// Semantic reconstruction of retail 0x00415E90.
int UpdateStageSequence(StageSequence&s,const std::vector<int>&ops,std::uint32_t input,int difficulty,int stage){if(s.cooldown>0)--s.cooldown;while(s.cursor<(int)ops.size()){int op=ops[s.cursor++];switch(op){case 0:return-1;case 1:case 2:s.handles[op-1]=0x1d+op;s.events.push_back(op);break;case 3:case 4:case 5:case 6:case 7:case 8:case 9:s.events.push_back(op);break;case 10:if(!(input&0x1001)&&s.cooldown){return 0;}s.cooldown=0;break;case 11:s.phase=stage;break;case 12:s.phase=difficulty;break;case 13:s.selection=difficulty*3+stage;break;case 14:case 15:case 16:case 17:case 18:case 19:case 20:case 21:case 22:case 23:s.events.push_back(op);break;}}++s.time;return 0;}
// Semantic reconstruction of retail 0x004236F0.
int UpdateReplaySave(ReplaySaveFlow&s,std::uint32_t in){++s.timer;switch(s.phase){case 6:if(s.timer>10&&(in&0x1001)){s.phase=7;s.timer=0;s.events.push_back(7);}break;case 7:if(s.timer>9){s.phase=8;s.timer=0;s.selection=0;s.name.fill(' ');s.name[8]=0;}break;case 8:if(in&0x10)s.selection=(s.selection+24)%25;if(in&0x20)s.selection=(s.selection+1)%25;if(in&0x1001){s.phase=9;s.cursor=0;s.timer=0;}if(in&0xa)s.phase=12;break;case 9:case 10:if(in&0x1001){if(s.cursor<8)s.name[s.cursor++]='A'+s.selection%26;else s.name[7]='A'+s.selection%26;}if(in&0xa){if(s.cursor)s.name[--s.cursor]=' ';else s.phase=8;}if(in&0x800){s.saved=true;s.phase=11;}break;case 11:if(s.timer>5)s.phase=12;break;case 12:s.events.push_back(12);s.phase=13;break;}return 1;}
// Semantic reconstruction of retail 0x0042E5A0.
void DrawOptions(OptionsView&s){s.sprites.fill(-1);s.sprites[0]=s.music/100+0x33;s.sprites[1]=(s.music/10)%10+0x33;s.sprites[2]=s.music%10+0x33;s.sprites[3]=s.sound/100+0x33;s.sprites[4]=(s.sound/10)%10+0x33;s.sprites[5]=s.sound%10+0x33;s.sprites[6]=s.window+0x40;s.sprites[7]=s.shots+0x48;s.sprites[8]=s.selection+0x50;}
// Semantic reconstruction of retail 0x0042F8B0.
void DrawMain(MainView&s){s.sprites.fill(-1);s.sprites[0]=s.value/10+0x33;s.sprites[1]=s.value%10+0x33;s.sprites[2]=s.selection+0x43;s.sprites[3]=s.difficulty+0x52;for(int i=4;i<20;++i)s.sprites[i]=0x60+i;}
// Semantic reconstruction of retail 0x00433EF0.
int UpdateMusicRoom(MusicRoom&s,std::uint32_t in,const std::string&r){if(s.phase==0){std::istringstream q(r);std::string line;while(std::getline(q,line))if(!line.empty()&&line[0]!='#')s.comments.push_back(line);s.track_count=s.comments.size();s.phase=1;s.timer=0;s.events.push_back(1);}else if(s.phase==1&&++s.timer>6)s.phase=2;else if(s.phase==2){if(in&0x10)s.selection=std::max(0,s.selection-1);if(in&0x20)s.selection=std::min(std::max(0,s.track_count-1),s.selection+1);if(in&0x1001)s.events.push_back(0x100+s.selection);if(in&0xa){s.phase=3;s.timer=0;}}else if(s.phase==3&&++s.timer>5)s.events.push_back(2);return 1;}
}
