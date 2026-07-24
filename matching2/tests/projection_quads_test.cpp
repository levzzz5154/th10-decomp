#include "th10/game/result_menu_open.hpp"
#include "th10/game/sprite_descriptor.hpp"
#include "th10/render/projection_quads.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

namespace {
void Identity(ProjectionMatrix* m){std::memset(m,0,sizeof(*m));for(int i=0;i<4;++i)m->m[i*5]=1;}
void Rot(ProjectionMatrix* m,float){Identity(m);} void Mul(ProjectionMatrix* o,const ProjectionMatrix* a,const ProjectionMatrix*){*o=*a;}
void ProjectWorld(ProjectionVec3* o,const ProjectionVec3* i,const ProjectionMatrix* w){o->x=i->x+w->m[12];o->y=i->y+w->m[13];o->z=i->z+w->m[14];}
void TestProjectedQuad(){ProjectedObject o={};Identity(&o.source_matrix);Identity(&o.world_matrix);o.scale_x=2;o.scale_y=3;o.base_position={10,20,0};o.flags=0xC|(1u<<18)|(2u<<20);ProjectionContext c={};ProjectionVec3 v[4];ProjectedQuadEnv e={Rot,Rot,Rot,Mul,ProjectWorld};assert(ProjectedQuad_Update(&o,&c,v,&e)==0);assert(o.world_matrix.m[0]==2&&o.world_matrix.m[5]==3);assert(v[0].x==10&&v[1].x==266);assert(v[0].y==-236&&v[2].y==20);assert(c.last_world.m[12]==10&&c.last_world.m[13]==20);assert((o.flags&0xC)==0);}
void ProjectBillboard(ProjectionVec3* o,const ProjectionVec3* i){*o=*i;}
void TestBillboard(){BillboardSource s={};s.width=4;s.height=2;s.scale_x=s.scale_y=1;s.base_position={10,10,.5f};s.flags=(1u<<18)|(1u<<20);BillboardEnv e={{12,10,.5f},ProjectBillboard};ProjectionVec3 v[4];assert(Billboard_BuildProjectedQuad(&s,v,&e)==0);assert(v[0].x==10&&v[1].x==14&&v[2].y==12);s.base_position.z=2;assert(Billboard_BuildProjectedQuad(&s,v,&e)==-1);}
void ProjectCull(ProjectionVec3* o,const ProjectionVec3* i,const ProjectionVec3* t){o->x=i->x+t->x;o->y=i->y+t->y;o->z=.5f;}
void TestCull(){ProjectionCullSource s={{0,0,0},{0,0,0}};ProjectionBox b={{0,0,0},{4,4,4}};ProjectionVec3 t={0,0,0};ProjectionCullEnv e={-10,10,-10,10,ProjectCull};assert(ProjectedBox_IsOutside(&s,&b,&t,100,&e)==0);t.x=30;assert(ProjectedBox_IsOutside(&s,&b,&t,100,&e)==1);}
SpriteResource g_res={8,12,30,34};SpriteNode g_node={55,&g_res};SpriteNode* Resolve(int){return &g_node;}int ToLong(float f){return (int)f;}
void TestDescriptor(){MenuWindowEnv e={Resolve,ToLong};MenuWindowDescriptor d={};d.sprite_handle=-1;assert(WindowDescriptor_Configure(&d,1,2,3,4,0x20,&e)==0);assert(d.sprite_handle==55&&d.x==2&&d.y==3&&d.width==4&&d.flags==0x20);assert(d.resource_08==8&&d.resource_0c==12&&d.resource_30==30&&d.resource_34==34);assert(WindowDescriptor_Configure(&d,1,0,0,0,0,&e)==-1);}
std::vector<int> scripts,slots;unsigned supervisor_flag;int positioned,bgm,seen;
void SetFlag(unsigned v){supervisor_flag=v;}int CreateEffect(int s,int l){assert(l==15);scripts.push_back(s);return 100+(int)s;}void Register(int){}void Position(int h,int x,int y,int w,int ht){assert(h==100&&x==32&&y==16&&w==384&&ht==448);positioned++;}void Bgm(const char*){bgm++;}void Sound(const char*,int s){slots.push_back(s);}void Seen(){seen++;}
void TestResultMenu(){float scale=0.5f;int shortcut=0;ResultMenuEnv e={};e.supervisor_result_state=&shortcut;e.frame_scale=&scale;e.set_supervisor_flag=SetFlag;e.create_effect=CreateEffect;e.register_effect=Register;e.position_window=Position;e.selected_handle=77;e.play_bgm=Bgm;e.extra_sound_enabled=true;e.load_sound=Sound;e.mark_result_seen=Seen;ResultMenu m={};scripts.clear();slots.clear();positioned=bgm=seen=0;ResultMenu_OpenRecovered(&m,&e);assert(m.state==6&&m.primary_owner==100&&m.secondary_owner==229&&m.selected_handle==77);assert(m.saved_frame_scale==.5f&&scale==1&&m.active==1);assert(scripts.size()==2&&scripts[0]==0&&scripts[1]==0x81);assert(slots.size()==2&&slots[0]==4&&slots[1]==2);e.supervisor_mode=1;e.input_flags=0x1000;ResultMenu_OpenRecovered(&m,&e);assert(shortcut==2);e.input_flags=0;ResultMenu_OpenRecovered(&m,&e);assert(shortcut==4);}
}
int main(){TestProjectedQuad();TestBillboard();TestCull();TestDescriptor();TestResultMenu();std::puts("BATCH19_TESTS_PASS");}
