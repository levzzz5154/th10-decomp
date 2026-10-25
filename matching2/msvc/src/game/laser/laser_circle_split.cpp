// 0041EFA0: remove circularly selected samples and spawn each surviving run.
// Written like TrimCircle (0041DD80): the counters come before the origin
// copy, the sample is read only through `sample` (the point field symbols
// then get retail's late ids, so point += step loads step first), and the
// line-animation creation is spelled out with the render-bucket clear
// through a pointer, as retail schedules it.
#include "../../../build_support/layout/ltcg/laser_cut/types.hpp"
#include <string.h>
#pragma code_seg(".text$f0041efa0F")
int CutLaser::CutCircle(const CutVector* center,float radius,int spawn_items) {
 int hit_count=0;
 int count=0;
 CutVector origin=position;
 char cut[256];
 memset(cut,0,sizeof(cut));
 float progress=6.0f;
 CutVector step;
 step.z=0.0f;
 step.SetPolar(angle,6.0f);
 CutVector point;
 point=step+position;
 point.z=0.0f;
 step*=2.0f;
 radius*=radius;
 {
  while (progress+6.0f<length) {
   CutVector* sample=&point;
   float dy=center->y-sample->y;
   float dx=center->x-sample->x;
   if (!(dx*dx+dy*dy>radius)) {
    cut[count]=1;
    ++hit_count;
    if (spawn_items && !sample->IsPartiallyOutside(32.0f,32.0f)) {
     g_item_manager->Spawn(sample,8,-1,-1.5707963705062866f,0.6f);
    }
    int index=script*2+17;
    void* resource=static_cast<CutAnimationBank*>(g_laser_manager)->line_animation;
    Entity* object=static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned int flags=object->flags_35C;
    object->flags_35C=flags|0x40000000u;
    int* bucket=&object->render_bucket;
    *bucket=0;
    object->position.x=sample->x+224.0f;
    object->position.z=sample->z;
    object->position.y=sample->y+16.0f;
    LoadScript2(static_cast<AnimationResourceFile*>(resource),
        reinterpret_cast<AnimationObjectFile*>(object),index);
    static_cast<CutAnimationLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
   }
   point+=step;
   progress+=12.0f;
   ++count;
  }
  if (hit_count) {
   int cursor=0;

   while (cursor<count && cut[cursor]) ++cursor;
   if (cursor) length=0.0f;
   else {
    int run=0;
    while (cursor<count && !cut[cursor]) {++cursor;++run;}
    if (cursor>=count) goto done;
    length=run*12.0f;
   }
   while (cursor<count) {
    while (cursor<count && cut[cursor]) ++cursor;
    if (cursor>=count) break;
    int run=0;
    int start=cursor;
    while (cursor<count && !cut[cursor]) {++cursor;++run;}
    CutSpawnParameters params;
    memset(&params,0,sizeof(params));
    params.length_limit=run*12.0f;
    params.length=params.length_limit;
    params.speed=8.0f;
    params.position=origin+step*static_cast<float>(start);
    params.angle=angle;
    params.width=width;
    params.type=type;
    params.script=script;
    params.total_length=total_length-start*12.0f;
    params.SpawnIn(g_laser_manager,0);
   }
  }
 }
done:
 return hit_count;
}
#pragma code_seg()
