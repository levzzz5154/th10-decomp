// 0041DD80: trim selected line-laser samples and preserve surviving runs.
#include "types.hpp"
#include <string.h>
#pragma code_seg(".text$f0041dd80F")
int TrimLaser::TrimCircle(const CutVector* center,float radius,int spawn_items) {
 CutVector origin=position;
 char cut[256];
 memset(cut,0,sizeof(cut));
 int hit_count=0;
 int count=0;
 float progress=6.0f;
 CutVector align_a;
 CutVector align_b;
 CutVector step;
 step.z=0.0f;
 step.SetPolar(angle,6.0f);
 CutVector point;
 point=step+position;
 point.z=0.0f;
 step*=2.0f;
 radius*=radius;
 {
  while (progress+6.0f<=length) {
   float dy=center->y-point.y;
   float dx=center->x-point.x;
   if (!(dx*dx+dy*dy>radius)) {
    cut[count]=1;
    ++hit_count;
    if (spawn_items && !(point.x+32.0f<=-192.0f) &&
        !(point.x-32.0f>=192.0f) && !(point.y+32.0f<=flt_0) &&
        !(point.y-32.0f>=448.0f)) {
     g_item_manager->Spawn(&point,8,-1,-1.5707963705062866f,0.6f);
    }
    int index=parameters.script*2+17;
    void* resource=static_cast<CutAnimationBank*>(g_laser_manager)->line_animation;
    Entity* object=static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned int flags=object->flags_35C;
    object->flags_35C=flags|0x40000000u;
    object->render_bucket=0;
    object->position.x=point.x+224.0f;
    object->position.z=point.z;
    object->position.y=point.y+16.0f;
    LoadScript2(static_cast<AnimationResourceFile*>(resource),
        reinterpret_cast<AnimationObjectFile*>(object),index);
    static_cast<CutAnimationLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
   }
   point+=step;
   progress+=12.0f;
   ++count;
  }

  if (!hit_count) goto done;
  if (hit_count>=count) {
   retired=1;
   return hit_count;
  }
  int cursor=0;
  while (cursor<count && cut[cursor]) ++cursor;
  if (cursor) {
   position+=step*static_cast<float>(cursor);
   float removed=static_cast<float>(cursor)*12.0f;
   length-=removed;
   if (length>18.0f) {
    parameters.length=length;
    traveled=removed;
   } else {retired=1;goto done;}
  }
  int first_run=0;
  while (cursor<count && !cut[cursor]) {++cursor;++first_run;}
  if (cursor>=count) goto done;
  float first_length=first_run*12.0f;
  parameters.length-=length-first_length;
  length=first_length;
  if (first_length<18.0f) retired=1;
  while (cursor<count) {
   while (cursor<count && cut[cursor]) ++cursor;
   if (cursor>=count) break;
   int run=0;
   int start=cursor;
   while (cursor<count && !cut[cursor]) {++cursor;++run;}
   float run_length=run*12.0f;
   CutSpawnParameters params=parameters;
   params.length_limit=run_length;
   params.length=run_length;
   if (run_length>18.0f) {
    params.position=origin+step*static_cast<float>(start);
    params.SpawnIn(g_laser_manager,0);
   }
  }
 }
done:
 return hit_count;
}
#pragma code_seg()
