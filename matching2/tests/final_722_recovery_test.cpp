#include "th10/game/ui_final_runtime.hpp"
#include "th10/game/gameplay_final_runtime.hpp"
#include "th10/render/final_quad_pipeline.hpp"
#include "th10/platform/final_input_runtime.hpp"
#include "th10/script/final_script_runtime.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
using namespace th10;
// test-side definitions of the ui_final retail globals (DAT_00476f78 is
// owned by animation_manager.cpp in this link set)
unsigned int DAT_00491fb8=0,DAT_00491ff4=0,DAT_00474c4c=0,DAT_00474c7c=0,DAT_00474c84=0,DAT_00474c8c=0;
unsigned int DAT_00474c68=0,DAT_00474c6c=0,DAT_00474c70=0,DAT_00474c74=0,DAT_00474ca0=0;
unsigned int DAT_00474e5c=0,DAT_00474e62=0;
unsigned char* DAT_004776f4=nullptr;
unsigned char* DAT_00477704=nullptr;
unsigned char* DAT_0047770c=nullptr;
unsigned char* DAT_0047783c=nullptr;
unsigned char* DAT_00477830=nullptr;
unsigned char* DAT_00477848=nullptr;
unsigned int DAT_00474c40=0;
unsigned short DAT_00474c48=0;
unsigned int DAT_00491c28=0;
float DAT_00476f78=1.0f;  // the frame-delta (animation_manager's copy may be GC'd)
static int observed_timer=0;
static int observed_invulnerable=0;
static int refetch_calls=0;
static int low_marks=0;
static int high_marks=0;
static int RefetchSprite(int sprite) { ++refetch_calls; return 900+sprite+refetch_calls; }
static void CountLowMark(int) { ++low_marks; }
static void CountHighMark(int) { ++high_marks; }
static bool OnlyHandle12IsLive(int handle) { return handle==12; }
static bool AllHandlesAreLive(int handle) { return handle!=0; }
static void ObservePlayerBeforeTail(gameplay_final::PlayerRuntime& player,
                                    std::uint32_t) {
    observed_timer=player.timer;
    observed_invulnerable=player.invulnerable;
}
static std::uint32_t AlwaysFive() { return 5u; }
static int rich_entry_calls=0;
static float rich_entry_radius[2]{};
static int rich_entry_origin[2]{};
static int rich_entry_mode[2]{};
static void RichEntry(float radius, int origin, int mode) {
    if (rich_entry_calls < 2) {
        rich_entry_radius[rich_entry_calls]=radius;
        rich_entry_origin[rich_entry_calls]=origin;
        rich_entry_mode[rich_entry_calls]=mode;
    }
    ++rich_entry_calls;
}
static int rich_respawn_calls=0;
static float rich_respawn_position[3]{};
static float rich_respawn_width=0.0f, rich_respawn_height=0.0f;
static int rich_respawn_frames=0, rich_respawn_mode=0;
static void RichRespawn(const float position[3], float width, float height,
                        int frames, int mode) {
    ++rich_respawn_calls;
    for (int i=0; i<3; ++i) rich_respawn_position[i]=position[i];
    rich_respawn_width=width; rich_respawn_height=height;
    rich_respawn_frames=frames; rich_respawn_mode=mode;
}
static int rich_refetch_calls=0;
static int rich_refetch_slots[4]{}, rich_refetch_sprites[4]{}, rich_refetch_layers[4]{};
static int RichRefetch(int slot, int sprite, int layer) {
    const int i=rich_refetch_calls++;
    if (i < 4) {
        rich_refetch_slots[i]=slot;
        rich_refetch_sprites[i]=sprite;
        rich_refetch_layers[i]=layer;
    }
    return 1000+i;
}
static gameplay_final::AttachedEffects* rich_effects_for_hook=nullptr;
static int rich_create_calls=0, rich_create_mode=0, rich_create_slot=0;
static int rich_create_script=0, rich_create_layer=0;
static std::uint32_t rich_create_flags=0;
static int RichCreate(int slot, int script, int layer, std::uint32_t flags) {
    ++rich_create_calls; rich_create_slot=slot; rich_create_script=script;
    rich_create_layer=layer; rich_create_flags=flags;
    rich_create_mode = rich_effects_for_hook->familiar_slots[slot].mode;
    return 2000+slot;
}
int main(){
 {ui_final::Notice n;ui_final::NoticeEnv e={};ui_final::QueueNotice(n,e,2,"abc",7);assert(n.slot==2&&n.text=="abc"&&(n.flags&1)&&n.score==0&&n.score_capped==0);}
 {ui_final::FrontTick s;s.transition=true;s.flags=0x10;s.timer=119;ui_final::FrontEnv e={};assert(ui_final::UpdateFront(s,e)==1&&s.mode==14&&s.timer==120&&s.position_words[0]==0);DAT_00491ff4=0x1000;ui_final::FrontTick s2;s2.transition=true;s2.flags=0x10;s2.timer=119;ui_final::UpdateFront(s2,e);assert(s2.mode==2);DAT_00491ff4=0;}
 {ui_final::StageSequence s;unsigned char st[]={100,0,1,0,100,0,2,0,100,0,3,0,100,0,0,0};s.script=st;s.frame_counter=100;ui_final::SequenceEnv e={};e.alloc_sprite=[](void*,int id){return id;};DAT_00474c7c=2;assert(ui_final::UpdateStageSequence(s,e)==-1&&s.handles[0]==29&&s.handles[1]==30&&s.handles[2]==90);ui_final::StageSequence t;unsigned char st2[]={100,0,2,0,200,0,0,0};t.script=st2;t.frame_counter=100;DAT_00474c7c=6;assert(ui_final::UpdateStageSequence(t,e)==0&&t.handles[1]==32);DAT_00474c7c=0;}
 {ui_final::ReplaySaveFlow s;s.timer=11;assert(ui_final::UpdateReplaySave(s,0x1001)==1&&s.phase==7);s.saved=true;s.timer=10;ui_final::UpdateReplaySave(s,0);assert(s.phase==8);ui_final::UpdateReplaySave(s,0x10);assert(s.selection==24);ui_final::UpdateReplaySave(s,0x1001);assert(s.phase==13);}
 {ui_final::OptionsView s;s.music=321;s.sound=45;s.selection=2;ui_final::DrawOptions(s);assert(s.sprites[0]==0x36&&s.sprites[2]==0x34&&s.sprites[3]==0x40&&s.sprites[8]==0x38);ui_final::MainView m;m.value=27;m.selection=1;ui_final::DrawMain(m);assert(m.sprites[0]==0x35&&m.sprites[1]==0x3a&&m.sprites[2]==0x35);}
 {ui_final::MusicRoom s;assert(ui_final::UpdateMusicRoom(s,0,"@a\n@b\n@c\n")==0&&s.track_count==3&&s.phase==0&&s.events.size()==8);s.timer=9;ui_final::UpdateMusicRoom(s,0,"");assert(s.phase==1);s.timer=4;ui_final::UpdateMusicRoom(s,0,"");assert(s.phase==2);ui_final::UpdateMusicRoom(s,0x20,"");assert(s.selection==1);ui_final::UpdateMusicRoom(s,0xa,"");assert(s.phase==3);}
 {gameplay_final::ItemPool p;gameplay_final::Item it;it.state=2;it.type=1;it.x=2.0f;it.y=1.0f;p.items.push_back(it);gameplay_final::ItemEnv e={};e.player_x=0;e.player_y=0;e.frame_delta=1;e.collect_l=-8;e.collect_t=-8;e.collect_r=8;e.collect_b=8;e.magnet_l=-8;e.magnet_t=-8;e.magnet_r=8;e.magnet_b=8;for(int i=0;i<20&&p.collected==0;++i)gameplay_final::UpdateItems(p,e);assert(p.collected==1&&p.items[0].state==0);}
 // Entry effects preserve the retail (radius, origin=0, mode) order.
 {gameplay_final::PlayerRuntime p; gameplay_final::PlayerStateEnv e={};
  p.state=0; e.player_present=false; e.hold_enabled=false; e.entry_effect_ex=RichEntry;
  rich_entry_calls=0; gameplay_final::UpdatePlayerState(p,0,&e);
  assert(rich_entry_calls==2&&std::fabs(rich_entry_radius[0]-64.0f)<1e-5f&&
         std::fabs(rich_entry_radius[1]-16.0f)<1e-5f&&rich_entry_origin[0]==0&&
         rich_entry_origin[1]==0&&rich_entry_mode[0]==1&&rich_entry_mode[1]==0); }
 {gameplay_final::PlayerRuntime p; gameplay_final::PlayerStateEnv env={};
  env.player_present=false; env.hold_enabled=false;
  p.state=0; gameplay_final::UpdatePlayerState(p,0,&env);
  assert(p.state==0&&p.y==48000&&p.timer==1);
  p.timer=59; gameplay_final::UpdatePlayerState(p,0,&env);
  assert(p.state==0&&p.y==48000-59*8000/60&&p.timer==60);
  gameplay_final::UpdatePlayerState(p,0,&env);
  assert(p.state==1&&p.timer==1);
  p.state=1; p.timer=0; p.power=50;
  env.player_present=true; env.focus_object=true; env.move=ObservePlayerBeforeTail;
  observed_timer=observed_invulnerable=0;
  gameplay_final::UpdatePlayerState(p,2,&env);
  assert(p.state==1&&p.power==30&&observed_timer==0&&observed_invulnerable==270&&
         p.invulnerable==269&&p.timer==1);
  p.state=4; p.timer=0; p.power=50; env.move=nullptr;
  gameplay_final::UpdatePlayerState(p,2,&env);
  assert(p.state==1&&p.power==30&&p.invulnerable==199&&p.timer==61);
  p.state=4; p.timer=30; p.timer_frac=30; p.invulnerable=0;
  env.move=nullptr; env.player_present=false;
  gameplay_final::UpdatePlayerState(p,0,&env);
  assert(p.state==0&&p.y==48000&&p.invulnerable==279&&p.timer==1); }
 // Respawn changes the global frame delta before the shared tail and passes
 // the allocator's exact (position, width, height, frames, mode) tuple.
 {gameplay_final::PlayerRuntime p; gameplay_final::PlayerStateEnv e={};
  p.state=2; p.timer=30; p.timer_frac=30.0f; p.px=12.0f; p.py=34.0f; p.pz=5.0f;
  e.frame_delta=2.0f; e.player_present=false; e.hold_enabled=false;
  e.respawn_effect_ex=RichRespawn; rich_respawn_calls=0;
  gameplay_final::UpdatePlayerState(p,0,&e);
  assert(rich_respawn_calls==1&&rich_respawn_position[0]==12.0f&&
         rich_respawn_position[1]==34.0f&&rich_respawn_position[2]==5.0f&&
         rich_respawn_width==32.0f&&rich_respawn_height==16.0f&&
         rich_respawn_frames==30&&rich_respawn_mode==150&&e.frame_delta==1.0f&&
         p.timer==1&&p.invulnerable==279); }
 // Countdown expiry keeps the retail timer initialized bit armed.
 {gameplay_final::PlayerRuntime p; gameplay_final::PlayerStateEnv e={};
  p.state=3; p.invulnerable=1; p.invuln_frac=1.0f;
  p.invulnerability_timer.flags=1; e.player_present=false; e.hold_enabled=false;
  gameplay_final::UpdatePlayerState(p,0,&e);
  assert(p.invulnerable==0&&(p.invulnerability_timer.flags&1u)!=0); }
 {gameplay_final::AttachedEffects e;e.handles={1,2,0,0};
  e.handle_live=AllHandlesAreLive;
  e.frame_linked=CountLowMark; e.flag_linked=CountHighMark;
  low_marks=high_marks=0; gameplay_final::UpdateAttachedEffects(e,50);
  assert(low_marks==2&&high_marks==0&&e.frame_states[0]==1&&e.frame_states[1]==1&&e.handles[0]==1&&
         e.animation_flags[0]==0&&e.events.empty());
  gameplay_final::UpdateAttachedEffects(e,100);
  assert(high_marks==2&&(e.animation_flags[0]&0x4000000)&&e.frame_states[0]==1&&
         e.handles[0]==0&&e.events.size()==2&&e.events[0]>=20&&e.events[0]<=22); }
 // High-path refetch uses the player ANM owner slot, sprite id, and layer 15.
 {gameplay_final::AttachedEffects e; e.difficulty=0; e.shot=1;
  e.handles={1,2,3,4}; e.handle_live=AllHandlesAreLive;
  e.refetch_animation=RichRefetch; rich_refetch_calls=0;
  gameplay_final::UpdateAttachedEffects(e,100);
  assert(rich_refetch_calls==4&&rich_refetch_slots[0]==0&&
         rich_refetch_slots[3]==3&&rich_refetch_sprites[0]==21&&
         rich_refetch_sprites[3]==21&&rich_refetch_layers[0]==15&&
         rich_refetch_layers[3]==15); }
 // High-path refetch clears every slot, including empty/stale records, while
 // only a live old handle receives the +0x35C flag and event report.
 {gameplay_final::AttachedEffects e; e.difficulty=0; e.shot=1;
  e.handles={0,11,12,0}; e.refetch_sprite=RefetchSprite;
  e.handle_live=OnlyHandle12IsLive; refetch_calls=0;
  gameplay_final::UpdateAttachedEffects(e,100);
  assert(refetch_calls==4&&e.handles[0]!=0&&e.handles[1]!=0&&
         e.handles[2]!=0&&e.handles[3]!=0&&e.events.size()==1&&
         e.events[0]==21&&e.animation_flags[1]==0&&
         (e.animation_flags[2]&0x4000000));
  e.handle_live=AllHandlesAreLive; e.familiar_count=4; gameplay_final::UpdateAttachedEffects(e,40);
  assert(e.frame_states[0]==1&&e.frame_states[1]==1&&e.frame_states[2]==1&&
         e.frame_states[3]==1&&(e.animation_flags[2]&0x4000000)); }
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
 {script_final::EclVm vm{};script_final::EclFunctionRecord rec{};script_final::EclScriptEntry tbl[4]={{"a",0x100},{"b",0x200},{"c",0x300},{"d",0x400}};script_final::EclScriptTable st{};st.count=4;st.entries=tbl;vm.current_record=&rec;vm.script_table=&st;assert(script_final::EclVm_BindSubroutine(&vm,"c")==0&&rec.resolved==0x310&&rec.name==0);assert(script_final::EclVm_BindSubroutine(&vm,"b")==0&&rec.resolved==0x210);script_final::EclVm_BindSubroutine(&vm,"missing");assert(rec.resolved==0);st.count=0;script_final::EclVm_BindSubroutine(&vm,"a");assert(rec.resolved==0);}
 // The player tail owns the 32 logical indicator records and the third
 // embedded timer. Scalar fields expose the exact linear/polar operations.
 {gameplay_final::PlayerRuntime p; p.state=3; p.timer=0; p.indicators.slots[0].flags=1;
  auto& slot=p.indicators.slots[0]; slot.timer_current=3; slot.timer_fraction=3;
  slot.position_x=10; slot.position_delta_x=2; slot.motion_x=3;
  slot.angle_step=3; slot.velocity_x=4;
  gameplay_final::PlayerStateEnv env={}; env.player_present=false; env.hold_enabled=false;
  gameplay_final::UpdatePlayerState(p,0,&env);
  assert(slot.position_x==12&&slot.motion_x==6&&slot.velocity_x==3&&
         slot.timer_previous==3&&slot.timer_current==2&&
         slot.timer_speed==&p.indicator_frame_delta&&(slot.flags&1));
  assert(p.auxiliary_timer.flags&1&&p.auxiliary_timer.current==1&&
         p.auxiliary_timer.target==0);
  slot.motion_flags=1; slot.angle=0; slot.angle_step=0; slot.radius=2;
  slot.radius_step=1; slot.velocity_x=.5f; slot.velocity_y=.25f;
  slot.position_delta_x=0; env.frame_delta=2;
  gameplay_final::UpdatePlayerState(p,0,&env);
  assert(slot.radius==3&&slot.motion_x==3.5f&&slot.motion_y==.25f&&
         slot.timer_previous==2&&slot.timer_current==0&&(slot.flags&1)==0); }
 // 0x00426F70's familiar records are distinct from the four effect handles.
 {gameplay_final::AttachedEffects e; e.difficulty=0; e.shot=1;
  e.formation.source_x=100; e.formation.source_y=200;
  e.formation.random_values={1,2,3,4};
  e.formation.create_animation=[](int index,int script){return 700+index+script;};
  gameplay_final::UpdateAttachedEffects(e,40);
  assert(e.familiar_count==2&&e.familiar_levels[0]==1&&e.familiar_levels[3]==1);
  assert(e.familiar_slots[0].mode==2&&e.familiar_slots[1].mode==2);
  assert(e.familiar_slots[0].script==0x12&&e.familiar_slots[0].handle==718);
  assert(e.familiar_slots[0].position_x==101&&e.familiar_slots[0].position_y==202&&
         e.familiar_slots[0].previous_x==101&&e.familiar_slots[0].previous_y==202);
  assert(e.familiar_slots[0].random[0]==1&&e.familiar_slots[0].random[1]==2&&
         e.familiar_slots[0].random[2]==3&&e.familiar_slots[0].random[3]==4);
  gameplay_final::UpdateAttachedEffects(e,20);
  assert(e.familiar_count==1&&e.familiar_slots[0].mode==2&&
         e.familiar_slots[1].mode==0&&e.familiar_slots[1].handle==719); }
 {gameplay_final::AttachedEffects e; e.difficulty=1; e.shot=0;
  e.formation.focus=true; e.formation.player_positions[0]={321,654};
  e.formation.history[0]=11; e.formation.history[1]=22;
  e.formation.random_word=[](){return 9u;};
  e.formation.create_animation=[](int,int script){return script;};
  e.formation.set_callback=[](int,int){};
  gameplay_final::UpdateAttachedEffects(e,20);
  assert(e.familiar_slots[0].position_x==321&&e.familiar_slots[0].position_y==654);
  assert(e.familiar_slots[0].previous_x==11&&e.familiar_slots[0].previous_y==22);
  assert(e.familiar_slots[0].script==0x11&&e.familiar_slots[0].callback_kind==1);
  assert(e.familiar_slots[0].handle==0x11&&e.formation.callback_order.size()==2&&
         e.formation.callback_order[0]==1&&e.formation.callback_order[1]==2); }
 // d=1/shot2 writes the computed position mirror and orders create, focus
 // initialization, and callback assignment as in 0x427381-0x427372.
 {gameplay_final::AttachedEffects e; e.difficulty=1; e.shot=2;
  e.formation.focus=true; e.formation.source_x=100; e.formation.source_y=200;
  e.formation.random_word=AlwaysFive;
  e.formation.create_animation=[](int,int script){return script;};
  e.formation.focus_init=[](int){}; e.formation.set_callback=[](int,int){};
  gameplay_final::UpdateAttachedEffects(e,20);
  assert(e.familiar_slots[0].position_x==105&&e.familiar_slots[0].position_y==205&&
         e.familiar_slots[0].random[2]==105&&e.familiar_slots[0].random[3]==205&&
         e.familiar_slots[0].script==0x13&&e.familiar_slots[0].callback_kind==2&&
         e.formation.callback_order.size()==3&&e.formation.callback_order[0]==2&&
         e.formation.callback_order[1]==3&&e.formation.callback_order[2]==1); }
 // Familiar mode is committed after the manager creates the ANM; creation
 // receives layer 15 and the ANM high flag before that commit.
 {gameplay_final::AttachedEffects e; e.difficulty=0; e.shot=0;
  e.familiar_slots[0].mode=7; rich_effects_for_hook=&e; rich_create_calls=0;
  e.formation.source_x=100; e.formation.source_y=200;
  e.formation.table_offsets_valid=true;
  e.formation.table_pair_a[0]={10,20}; e.formation.table_pair_b[0]={30,40};
  e.formation.create_animation_ex=RichCreate;
  gameplay_final::UpdateAttachedEffects(e,20);
  assert(rich_create_calls==1&&rich_create_slot==0&&rich_create_script==0x11&&
         rich_create_layer==15&&rich_create_flags==0x40000000u&&
         rich_create_mode==7&&e.familiar_slots[0].mode==2&&
         e.familiar_slots[0].handle==2000&&
         e.familiar_slots[0].position_x==110&&e.familiar_slots[0].position_y==220&&
         e.familiar_slots[0].random[0]==10&&e.familiar_slots[0].random[3]==40); }
 // Excess familiar records use the low +0x304 frame mark, not the high
 // retirement flag, and retain their manager-owned handle word.
 {gameplay_final::AttachedEffects e; e.difficulty=2; e.familiar_count=2;
  e.familiar_slots[1].mode=2; e.familiar_slots[1].handle=77;
  e.handle_live=AllHandlesAreLive; e.frame_linked=CountLowMark; low_marks=0;
  gameplay_final::UpdateAttachedEffects(e,20);
  assert(low_marks==1&&e.familiar_slots[1].mode==0&&
         e.familiar_slots[1].handle==77); }
 std::cout<<"FINAL_722_RECOVERY_TESTS_PASS\n";
}
