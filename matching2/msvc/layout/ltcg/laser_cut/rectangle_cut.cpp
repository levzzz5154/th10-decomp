// 0041EB00: remove rectangularly selected samples and spawn each surviving run.
#include "types.hpp"
#include <string.h>
#pragma code_seg(".text$f0041eb00F")
int CutLaser::CutRectangle(const CutVector* center,const CutVector* size,int spawn_items) {
 CutVector origin=position;
 char cut[256];
 memset(cut,0,sizeof(cut));
 int hit_count=0;
 int count=0;
 float progress=6.0f;
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

 {
  while (progress+6.0f<length) {
   if (!(point.x<low.x) && !(point.x>high.x) &&
       !(point.y<low.y) && !(point.y>high.y)) {
    cut[count]=1;
    ++hit_count;
    CutVector* sample_position=&point;
    if (spawn_items && !sample_position->IsPartiallyOutside(32.0f,32.0f)) {
     data_00477818->Spawn(sample_position,8,-1,-1.5707963705062866f,0.6f);
    }
    int index=script*2+17;
    void* resource=static_cast<CutAnimationBank*>(data_0047781c)->line_animation;
    reinterpret_cast<CutAnimationResource*>(resource)->CreateOffset(index,&point);
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
    params.SpawnIn(data_0047781c,0);
   }
  }
 }
done:
 return hit_count;
}
#pragma code_seg()
