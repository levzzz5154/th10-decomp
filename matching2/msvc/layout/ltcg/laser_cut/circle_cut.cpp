// 0041EFA0: remove circularly selected samples and spawn each surviving run.
#include "types.hpp"
#include <string.h>
#pragma code_seg(".text$f0041efa0F")
int CutLaser::CutCircle(const CutVector* center,float radius,int spawn_items) {
 CutVector origin=position;
 char cut[256];
 memset(cut,0,sizeof(cut));
 int hit_count=0;
 int count=0;
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
   float dy=center->y-point.y;
   float dx=center->x-point.x;
   if (!(dx*dx+dy*dy>radius)) {
    cut[count]=1;
    ++hit_count;
    if (spawn_items && !(point.x+32.0f<=-192.0f) &&
        !(point.x-32.0f>=192.0f) && !(point.y+32.0f<=data_00470b04) &&
        !(point.y-32.0f>=448.0f)) {
     data_00477818->Spawn(&point,8,-1,-1.5707963705062866f,0.6f);
    }
    int index=script*2+17;
    void* resource=static_cast<CutAnimationBank*>(data_0047781c)->line_animation;
    Entity* object=static_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned int flags=object->flags_35C;
    object->flags_35C=flags|0x40000000u;
    object->render_bucket=0;
    object->position.x=point.x+224.0f;
    object->position.z=point.z;
    object->position.y=point.y+16.0f;
    LoadScript_0043e710(static_cast<AnimationResource_0043e710*>(resource),
        reinterpret_cast<AnimationObject_0043e710*>(object),index);
    static_cast<CutAnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
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
    params.script=script;
    params.width=width;
    params.type=type;
    params.total_length=total_length-start*12.0f;
    params.SpawnIn(data_0047781c,0);
   }
  }
 }
done:
 return hit_count;
}
#pragma code_seg()
