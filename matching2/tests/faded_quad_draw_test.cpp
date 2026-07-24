#include "th10/render/anm_record_walk.hpp"
#include "th10/render/faded_quad_draw.hpp"
#include <cassert>
#include <cstdio>
#include <cstring>

namespace {
void Identity(ProjectionMatrix* m){std::memset(m,0,sizeof(*m));for(int i=0;i<4;++i)m->m[i*5]=1;}
void Rot(ProjectionMatrix* m,float){Identity(m);}void Mul(ProjectionMatrix* o,const ProjectionMatrix* a,const ProjectionMatrix*){*o=*a;}
void Project(ProjectionVec3* o,const ProjectionVec3* i,const ProjectionMatrix* w){*o={i->x+w->m[12],i->y+w->m[13],i->z+w->m[14]};}
void Transform(ProjectionVec3* o,const ProjectionVec3* i,const ProjectionMatrix* w){Project(o,i,w);}FadeColorVertex saved[4];int render_mode;
void Render(FadeColorVertex v[4],int m){std::memcpy(saved,v,sizeof(saved));render_mode=m;}
void TestFade(){FadeQuad q={};Identity(&q.projection.source_matrix);Identity(&q.projection.world_matrix);q.projection.scale_x=q.projection.scale_y=1;q.projection.flags=(1u<<18)|(1u<<20);q.primary_color=0xFF804020;q.alternate_color=0xFF112233;ProjectionContext c={};ProjectedQuadEnv pe={Rot,Rot,Rot,Mul,Project};FadeQuadEnv e={};e.projection_context=&c;e.project_env=&pe;e.camera_position={0,0,0};e.near_distance=5;e.far_distance=15;e.far_color=0xFF000000;for(int i=0;i<4;++i)e.source_points[i]={(float)i,0,0};e.transform=Transform;e.render=Render;FadedProjectedQuad_Draw(&q,&e);assert(render_mode==2);assert(saved[0].color==q.primary_color);assert(saved[0].rhw==1);q.projection.flags|=0x8000;FadedProjectedQuad_Draw(&q,&e);assert(saved[0].color==q.alternate_color);}
void CullProject(ProjectionVec3* o,const ProjectionVec3* i,const ProjectionVec3* t){*o={i->x+t->x,i->y+t->y,.5f};}int special_calls,draws;bool special_value;
void Special(bool v){++special_calls;special_value=v;}void DrawVm(AnmRecordVm*){++draws;}
void TestWalk(){ProjectionCullSource cs={{0,0,0},{0,0,0}};ProjectionCullEnv ce={-10,10,-10,10,CullProject};AnmRecordVm vm={0x02000000u,{0,0,0},1,1,4,8};AnmRecordSlot slots[2]={{0,&vm,{1,2,3},16,12},{1,&vm,{0,0,0},0,0}};AnmRecord accepted={1,7,0,{{0,0,0},{2,2,2}},{1,1,0},slots,2};AnmRecord rejected={2,7,0,{{50,0,0},{2,2,2}},{0,0,0},slots,2};AnmRecord* records[2]={&accepted,&rejected};AnmRecordWalkState st={records,2,&cs,10000,0,0,0};AnmRecordWalkEnv e={&ce,Special,DrawVm};special_calls=draws=0;assert(AnmRecordTable_DrawVisible(&st,7,&e)==0);assert(st.accepted_count==1&&st.rejected_count==1&&st.drawn_vm_count==1);assert((accepted.flags&2)!=0&&draws==1&&special_calls==1&&special_value);assert(vm.position.x==2&&vm.position.y==3&&vm.position.z==3);assert(vm.scale_x==2&&vm.scale_y==3&&(vm.flags&8));}
}
int main(){TestFade();TestWalk();std::puts("BATCH20_TESTS_PASS");}
