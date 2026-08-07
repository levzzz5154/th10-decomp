#include "th10/game/event_script_runtime.hpp"
#include "th10/game/projectile_command_runtime.hpp"
#include "th10/game/player_front_runtime.hpp"
#include "th10/platform/midi_event_runtime.hpp"
#include "th10/game/replay_large_runtime.hpp"
#include "th10/render/anchored_quad_draw.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
// Frame-delta sentinel for the 0x004250B0 movement scaling (DAT_00476f78;
// the runtime default is 1.0f). Defined test-side here - the link set has no
// other owner.
float DAT_00476f78 = 1.0f;
using namespace th10;
int main(){
 {event_script::EndingState s;std::vector<event_script::EndingCommand>v{{0,9,{0x123456},{}},{0,7,{},{}},{0,0,{},{}}};event_script::EndingEdges e{};assert(event_script::EndingScript_Update(s,v,1,e)==0&&s.color==0x123456&&(s.flags&4));}
 // 0x0040BD80 cases 3/5/8 are retail text-draw / countdown-timer / ANM
 // create ops, not modeled: the host edge is the adapter boundary.
 {event_script::EndingState s;std::vector<event_script::EndingCommand>v{{0,3,{100},{}},{0,5,{60},{}},{0,8,{0,1,2},{}}};int calls=0;event_script::EndingEdges e{&calls,[](void*c,int,const event_script::EndingCommand&){++*(int*)c;},nullptr};assert(event_script::EndingScript_Update(s,v,1,e)==0&&calls==3&&s.time==1);}
 {event_script::StageState s;std::vector<event_script::StageCommand>v{{0,2,{1,2,3}},{0,8,{287454016.0f}},{0,13,{9}}};event_script::StageTimeline_Update(s,v,1,{});assert(s.camera[2]==3&&s.global_value==9&&s.time==1);}
 // 0x00403C80 case 1 scene jump: time=arg1, cursor jumps to args[0],
 // and the hard stop (case 0) skips the frame time advance.
 {event_script::StageState s;std::vector<event_script::StageCommand>v{{0,1,{2,50}},{0,13,{7}},{0,0,{}}};event_script::StageTimeline_Update(s,v,1,{});assert(s.time==50&&s.previous_time==49&&s.cursor==3);}
 {projectile_commands::State s;std::vector<projectile_commands::Command>v(4);v[0].opcode=0x10;v[0].a={2,3,4};v[1].opcode=0x400000;v[2].opcode=0x8000;v[2].a[2]=7;v[3].opcode=0;projectile_commands::Apply(s,v,{});assert(s.speed==2&&s.angle==3&&s.spawn_count==1&&s.sound==7);}
 {player_front::Player p;p.x=0x47df;p.y=0xc81;player_front::PlayerEdges e{nullptr,nullptr,nullptr};player_front::UpdatePlayer(p,0x20|4,true,10,3,e);assert(p.direction==2&&p.slow&&p.x<=0x47e0&&p.trail[0][0]==p.x);}
 {player_front::Player d;player_front::UpdatePlayer(d,0x10|0x80,true,10,3,{});assert(d.direction==6);player_front::UpdatePlayer(d,0x20|0x40,true,10,3,{});assert(d.direction==7);}
 {player_front::Front f;player_front::InitializeFront(f,{3,39,0,2,4,false,true,true});assert(f.lives[2]&&!f.lives[3]&&f.digits[0]==9&&f.animations.back()==0x6f);}
 {midi::State s;midi::Track t{{0x90,60,100,0,60,0,0},0};assert(midi::ProcessEvent(s,t)&&s.channels[0].notes[60]);assert(midi::ProcessEvent(s,t)&&!s.channels[0].notes[60]);midi::Track end{{0xff,0x2f,0},0};assert(!midi::ProcessEvent(s,end)&&end.ended);}
 {replay_large::Replay r;r.rank=2;r.score=123;r.slow_rate=1.5f;r.stages[0].present=true;r.stages[0].header={1,1,1};auto o=replay_large::Serialize(r,"PLAYERLONG");assert(r.name[0]=='P'&&r.name[7]=='O'&&o.header.size()==0x2c&&o.user_text.size()%4==0&&o.user_notice.size()%4==0);}
 {replay_large::InputMenu s;replay_large::UpdateInputMenu(s,0,{});assert(s.phase==1);s.timer=7;replay_large::UpdateInputMenu(s,0,{});assert(s.phase==2);replay_large::UpdateInputMenu(s,0x20,{});assert(s.selection==1);replay_large::UpdateInputMenu(s,0xa,{});assert(s.phase==3);}
 {render::AnchoredQuad s;s.width=20;s.height=10;s.position={100,50,3};auto q=render::BuildAnchoredQuad(s);assert(q.v[0].x==90&&q.v[2].y==55&&q.v[3].z==3);s.flags=(1u<<18)|(2u<<20);q=render::BuildAnchoredQuad(s);assert(q.v[0].x==100&&q.v[0].y==40);}
 std::cout<<"NEXT10_LARGE_RECOVERY_TESTS_PASS\n";
}
