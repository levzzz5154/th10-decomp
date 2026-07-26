#include "th10/game/enemy_projectile_spawn.hpp"
#include "th10/game/replay_menu_runtime.hpp"
#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
using namespace th10::enemy_projectile;
using namespace th10::replay_menu;
struct C{std::vector<std::string>log;std::vector<ReplaySummary*>owned;bool save_ok=true;int launched=-1;};
static float rnd(void*,float a){return a*.25f;}static void motion(SpawnSlot&s){s.color=7;}static void pub(SpawnSlot&s){assert(s.color==7);s.animation=9;}
static ReplaySummary* load(void*v,const std::string&f){auto*c=(C*)v;c->log.push_back("load:"+f);auto*q=new ReplaySummary;q->stage_present[1]=1;q->stage_present[4]=1;c->owned.push_back(q);return q;}static void release(void*v,ReplaySummary*q){((C*)v)->log.push_back("release");(void)q;}static std::vector<std::string> enumerate(void*){return {"th10_ud0001.rpy","th10_ud0002.rpy"};}static void trans(void*v,int p){((C*)v)->log.push_back("t"+std::to_string(p));}static void sound(void*v,int p){((C*)v)->log.push_back("s"+std::to_string(p));}static void launch(void*v,const ReplaySummary&,int st,int){((C*)v)->launched=st;}static bool save(void*v,const std::string&f,const char*n){auto*c=(C*)v;c->log.push_back("save:"+f+":"+n);return c->save_ok;}
int main(){
 {SpawnPool p; p.slots.resize(4);p.slots[0].active=p.slots[1].active=true;p.cursor=0;SpawnDescriptor d;d.x=3;d.y=4;d.z=.2f;d.spacing=.5f;d.speed0=5;d.speed1=1;d.rows=4;d.columns=8;d.layout=3;d.flags=4;d.type=6;d.variant=2;d.payload[3]=44;SpawnEdges e{rnd,nullptr,motion,pub};assert(EnemyProjectile_SpawnOne(p,d,2,1,1,e));auto&s=p.slots[2];assert(s.active&&s.state==8&&s.type==6&&s.payload[3]==44&&s.animation==9);assert(std::fabs(s.speed-4)<.001f);assert(p.cursor==3);}
 {SpawnPool p;p.slots.resize(3);for(auto&s:p.slots)s.active=true;SpawnDescriptor d;assert(!EnemyProjectile_SpawnOne(p,d,0,0,0,{}));p.slots[1].active=false;p.cursor=2;d.layout=8;d.spacing=4;d.speed1=8;d.flags=2;int order=0;SpawnEdges e{rnd,nullptr,+[](SpawnSlot&s){assert(s.state==7);s.color=1;},+[](SpawnSlot&s){assert(s.color==1);}};assert(EnemyProjectile_SpawnOne(p,d,0,0,0,e));assert(p.slots[1].speed==10);(void)order;}
 {C c;ReplayMenuState s;ReplayMenuEdges e{enumerate,&c,load,release,trans,sound,launch};ReplayLoadMenu_Update(s,0,e);assert(s.phase==1&&s.slots[0]&&s.slots[26]);s.timer=7;ReplayLoadMenu_Update(s,0,e);assert(s.phase==2);ReplayLoadMenu_Update(s,0x20,e);assert(s.selection==1);ReplayLoadMenu_Update(s,0x1001,e);assert(s.phase==4&&s.stage_count==2);s.timer=15;ReplayLoadMenu_Update(s,0x20,e);assert(s.chosen_stage==1);ReplayLoadMenu_Update(s,0x1001,e);assert(s.phase==3);s.timer=32;ReplayLoadMenu_Update(s,0,e);assert(c.launched==4);}
 {C c;ReplayMenuState s;s.phase=2;s.selection=49;ReplayMenuEdges e{nullptr,&c,nullptr,nullptr,trans,sound,nullptr};ReplayLoadMenu_Update(s,0x20,e);assert(s.selection==0);ReplayLoadMenu_Update(s,0x0a,e);assert(s.phase==5);}
 {C c;ReplayNameState s;ReplayNameEdges e{load,release,save,&c,trans,sound};ReplaySaveName_Update(s,0,e);assert(s.phase==1&&s.slots[24]);s.timer=7;ReplaySaveName_Update(s,0,e);assert(s.phase==2);ReplaySaveName_Update(s,0x1001,e);assert(s.phase==3&&s.cursor==0);s.selection=0;ReplaySaveName_Update(s,0x1001,e);assert(s.name[0]=='A'&&s.cursor==1);s.selection=1;ReplaySaveName_Update(s,0x1001,e);assert(s.name[1]=='B');ReplaySaveName_Update(s,0x0a,e);assert(s.cursor==1&&s.name[1]==' ');s.selection=72;ReplaySaveName_Update(s,0x1001,e);assert(s.phase==2);assert(c.log.back()=="s0");}
 {C c;c.save_ok=false;ReplayNameState s;s.phase=3;s.slot=2;s.selection=72;s.name={'X',' ',' ',' ',' ',' ',' ',' ','\0'};ReplayNameEdges e{load,release,save,&c,trans,sound};ReplaySaveName_Update(s,0x1001,e);assert(s.phase==3);assert(c.log[0].find("save:th10_03.rpy:X")!=std::string::npos);}
 std::cout<<"LARGE_RECOVERY_PASS_TESTS_PASS\n";
}
