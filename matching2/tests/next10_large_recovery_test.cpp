#include "th10/game/stage_tip_parser.hpp"
#include "th10/game/event_script_runtime.hpp"
#include "th10/game/projectile_command_runtime.hpp"
#include "th10/game/player_front_runtime.hpp"
#include "th10/platform/midi_event_runtime.hpp"
#include "th10/game/replay_large_runtime.hpp"
#include "th10/render/anchored_quad_draw.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
using namespace th10;
int main(){
 {auto r=stage_tips::ParseStageTips("Version: 0.0\nStage: 2\nTips:\nPos: 10,20\nText: \"hello\"\nScale: 9\nColor: 1,2,3\nAlpha: 4\nEnd:\nStageEnd:\n",false);assert(r.opened&&r.version_ok&&r.tips.size()==2);assert(r.tips[0].scale==4&&r.tips[0].text=="hello"&&r.tips[1].list_index==36);auto bad=stage_tips::ParseStageTips("Version: 1.0\n",true);assert(!bad.version_ok);}
 {event_script::EndingState s;std::vector<event_script::EndingCommand>v{{0,9,{0x123456},{}},{0,7,{},{}},{0,0,{},{}}};event_script::EndingEdges e{};assert(event_script::EndingScript_Update(s,v,1,e)==0&&s.color==0x123456&&(s.flags&4));}
 {event_script::StageState s;std::vector<event_script::StageCommand>v{{0,2,{1,2,3}},{0,8,{287454016.0f}},{0,13,{9}}};event_script::StageTimeline_Update(s,v,1,{});assert(s.camera[2]==3&&s.global_value==9&&s.time==1);}
 {projectile_commands::State s;std::vector<projectile_commands::Command>v(4);v[0].opcode=0x10;v[0].a={2,3,4};v[1].opcode=0x400000;v[2].opcode=0x8000;v[2].a[2]=7;v[3].opcode=0;projectile_commands::Apply(s,v,{});assert(s.speed==2&&s.angle==3&&s.spawn_count==1&&s.sound==7);}
 {player_front::Player p;p.x=0x47df;p.y=0xc81;int n=0;player_front::PlayerEdges e{&n,+[](void*v,int){++*(int*)v;}};player_front::PlayerSpeeds s{450,200,318,141,1.0f};
  // 0x20 is retail's "down" bit and 0x04 is focus, so the focused straight
  // speed moves the player down and the horizontal step stays zero.
  player_front::UpdatePlayer(p,0x20|4,true,5,s,e);assert(p.direction==2&&p.slow&&p.slow_age==0&&p.x==0x47df&&p.y==0xc81+200&&p.trail[0][0]==p.x&&n==0);
  // 0x50 is up+left: both steps take the focused diagonal speed, and the
  // horizontal one going negative fires the lean interrupt.
  player_front::UpdatePlayer(p,0x50|4,true,5,s,e);assert(p.direction==5&&p.x==0x47df-141&&p.y==0xc81+200-141&&n==1);}
 {player_front::Front f;player_front::InitializeFront(f,{3,39,0,2,4,false,true,true});assert(f.lives[2]&&!f.lives[3]&&f.digits[0]==9&&f.animations.back()==0x6f);}
 {midi::State s;midi::Track t{{0x90,60,100,0,60,0,0},0};assert(midi::ProcessEvent(s,t)&&s.channels[0].notes[60]);assert(midi::ProcessEvent(s,t)&&!s.channels[0].notes[60]);midi::Track end{{0xff,0x2f,0},0};assert(!midi::ProcessEvent(s,end)&&end.ended);}
 {replay_large::Replay r;r.rank=2;r.score=123;r.slow_rate=1.5f;r.stages[0].present=true;r.stages[0].header={1,1,1};auto o=replay_large::Serialize(r,"PLAYERLONG");assert(r.name[0]=='P'&&r.name[7]=='O'&&o.header.size()==0x2c&&o.user_text.size()%4==0&&o.user_notice.size()%4==0);}
 {replay_large::InputMenu s;replay_large::UpdateInputMenu(s,0,{});assert(s.phase==1);s.timer=7;replay_large::UpdateInputMenu(s,0,{});assert(s.phase==2);replay_large::UpdateInputMenu(s,0x20,{});assert(s.selection==1);replay_large::UpdateInputMenu(s,0xa,{});assert(s.phase==3);}
 {render::AnchoredQuad s;s.width=20;s.height=10;s.position={100,50,3};auto q=render::BuildAnchoredQuad(s);assert(q.v[0].x==90&&q.v[2].y==55&&q.v[3].z==3);s.flags=(1u<<18)|(2u<<20);q=render::BuildAnchoredQuad(s);assert(q.v[0].x==100&&q.v[0].y==40);}
 std::cout<<"NEXT10_LARGE_RECOVERY_TESTS_PASS\n";
}
