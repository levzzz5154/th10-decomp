#include "th10/game/ui_final_runtime.hpp"
#include "th10/game/gameplay_final_runtime.hpp"
#include "th10/render/final_quad_pipeline.hpp"
#include "th10/platform/final_input_runtime.hpp"
#include "th10/script/final_script_runtime.hpp"
#include <cassert>
#include <iostream>
using namespace th10;
int main(){
 {ui_final::Notice n;ui_final::QueueNotice(n,2,"abc",7,3,4);assert(n.count==1&&n.animations[0]==0x23&&n.animations[1]==0x34);}
 {ui_final::FrontTick s;s.boss_active=true;s.transition=true;s.timer=120;assert(ui_final::UpdateFront(s)==1&&s.mode==14&&s.events.size()==17);}
 {ui_final::StageSequence s;std::vector<int>o{1,13,0};ui_final::UpdateStageSequence(s,o,0,2,4);assert(s.handles[0]&&s.selection==10);}
 {ui_final::ReplaySaveFlow s;s.timer=11;ui_final::UpdateReplaySave(s,0x1001);assert(s.phase==7);s.timer=10;ui_final::UpdateReplaySave(s,0);assert(s.phase==8);}
 {ui_final::OptionsView s;s.music=321;s.sound=45;s.selection=2;ui_final::DrawOptions(s);assert(s.sprites[0]==0x36&&s.sprites[8]==0x52);ui_final::MainView m;m.value=27;m.selection=1;ui_final::DrawMain(m);assert(m.sprites[0]==0x35&&m.sprites[2]==0x44);}
 {ui_final::MusicRoom s;ui_final::UpdateMusicRoom(s,0,"#c\na\nb\n");assert(s.track_count==2&&s.phase==1);s.timer=7;ui_final::UpdateMusicRoom(s,0,"");assert(s.phase==2);ui_final::UpdateMusicRoom(s,0x20,"");assert(s.selection==1);}
 {gameplay_final::ItemPool p;p.items={{2,1,0,0,0,0,0,0,0,true}};gameplay_final::UpdateItems(p,0,0,1,1);assert(p.collected==1&&!p.items[0].active);}
 {gameplay_final::PlayerRuntime p;p.state=1;p.bombs=1;p.lives=3;gameplay_final::UpdatePlayerState(p,2);assert(p.state==2&&p.bombs==0);p.timer=91;gameplay_final::UpdatePlayerState(p,0);assert(p.state==1);}
 {gameplay_final::AttachedEffects e;e.handles={1,2,0,0};gameplay_final::UpdateAttachedEffects(e,50);assert(e.states[0]&0x4000000&&!e.events.empty());}
 // 0x00442670. Corner order is {left,top} {right,top} {left,bottom}
 // {right,bottom}; mode 1 snaps, mode bit 1 clear overrides the colour.
 {static int flushes;static unsigned int lastTexture;static unsigned int lastFlags;static int appends;
  flushes=appends=0;lastTexture=0;lastFlags=0;
  QuadSubmitSprite sprite{7u,0.f,0.f,1.f,1.f};
  QuadSubmitVm vm{};vm.flags=0u;vm.color_primary=9u;vm.color_secondary=5u;vm.sprite=&sprite;
  QuadSubmitManager manager{0.f,0.f,0u,0xFF,0,{0,0,0,0},0u,0u,100u,100u};
  QuadSubmitEnv env{[]{++flushes;},[](unsigned int t){lastTexture=t;},
                    [](unsigned int f){lastFlags=f;},
                    [](const QuadSubmitVertex*){++appends;}};
  QuadSubmitVertex quad[4]={{1.4f,1.4f,0,1,0,0,0},{10.4f,1.4f,0,1,0,0,0},
                            {1.4f,10.4f,0,1,0,0,0},{10.4f,10.4f,0,1,0,0,0}};
  assert(Quad_SubmitFinal(quad,&vm,&manager,&env,1)==0);
  assert(quad[0].x==.5f&&quad[3].y==9.5f&&quad[0].color==9u);
  assert(lastTexture==7u&&lastFlags==0u&&manager.textured==1&&flushes==2&&appends==1);
  // Wholly outside the clip rectangle: nothing is staged.
  QuadSubmitVertex away[4]={{200,200,0,1,0,0,0},{210,200,0,1,0,0,0},
                            {200,210,0,1,0,0,0},{210,210,0,1,0,0,0}};
  assert(Quad_SubmitFinal(away,&vm,&manager,&env,1)==0&&appends==1);}
 {input_final::State s;std::array<std::uint8_t,256>k{};std::array<int,16>m{};for(int i=0;i<16;++i)m[i]=i;k[3]=0x80;assert(input_final::Poll(s,k,m,0,true)==8&&s.pressed==8);bool repeated=false;for(int i=0;i<26;++i){input_final::Poll(s,k,m,0,true);repeated|=bool(s.repeat&8);}assert(repeated);k[3]=0;input_final::Poll(s,k,m,0,true);assert(s.released&8);}
 {script_final::EntityVm s;std::vector<script_final::Instruction>v(3);v[0].opcode=12;v[0].i[0]=1;v[0].i[1]=4;v[1].opcode=14;v[1].i[0]=1;v[1].i[1]=3;v[2].opcode=0;assert(script_final::TickEntityVm(s,v)==-1&&s.iv[1]==7);}
 {script_final::ParseState s;assert(script_final::ParseScript(s,"0x0c 1 4\n#x\n0 0\n")&&s.instructions.size()==2);assert(!script_final::ParseScript(s,"bad 1\n"));}
 {script_final::EclState s;s.opcode=0x100;s.f[0]=2;s.f[1]=3;script_final::ExecuteEcl(s);assert(s.flags&0x40000&&s.f[8]==2);s.opcode=0x107;s.i[0]=4;s.i[1]=5;script_final::ExecuteEcl(s);assert(s.i[10]==6);s.opcode=0x1a4;script_final::ExecuteEcl(s);assert(s.flags&0x1000);s.opcode=0x1a5;script_final::ExecuteEcl(s);assert(!(s.flags&0x1000));}
 std::cout<<"FINAL_722_RECOVERY_TESTS_PASS\n";
}
