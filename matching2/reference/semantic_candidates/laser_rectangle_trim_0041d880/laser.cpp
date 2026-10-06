// 0041D880: trim selected line-laser samples and preserve surviving runs.
#include "types.hpp"
#include <string.h>
#pragma code_seg(".text$45rectangletrim")
int TrimLaser::TrimRectangle(const CutVector* center,const CutVector* size,int spawn_items) {
 CutVector origin=position;
 char cut[256];
 memset(cut,0,sizeof(cut));
 int hit_count=0;
 int count=0;
 volatile float progress=6.0f;
 CutVector high;high=(*size)*0.5f;
 CutVector low;low=(*center)-high;
 high=high+(*center);
 CutVector step;
 step.z=0.0f;
 step.SetPolar(angle,6.0f);
 CutVector point;
 point=step+position;
 point.z=0.0f;
 step*=2.0f;

 if (12.0f<=length) {
  do {
   if (!(point.x<low.x) && !(point.x>high.x) &&
       !(point.y<low.y) && !(point.y>high.y)) {
    cut[count]=1;
    ++hit_count;
    CutVector* sample_position=&point;
    if (spawn_items && !sample_position->IsPartiallyOutside(32.0f,32.0f)) {
     data_00477818->Spawn(sample_position,8,-1,-1.5707963705062866f,0.6f);
    }
    int index=parameters.script*2+17;
    void* resource=static_cast<CutAnimationBank*>(data_0047781c)->line_animation;
    reinterpret_cast<CutAnimationResource*>(resource)->CreateOffset(index,&point);
   }
   ++count;
   point+=step;
   progress+=12.0f;
  } while (progress+6.0f<=length);

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
   } else {retired=1;return hit_count;}
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
    params.SpawnIn(data_0047781c,0);
   }
  }
 }
done:
 return hit_count;
}
#pragma code_seg()
