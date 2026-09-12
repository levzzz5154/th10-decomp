#include "th10/game/stage_focus_fade.hpp"
#include <cmath>
namespace { StageFocusEntity* Find(uint32_t h,StageFocusNode*n){for(;n;n=n->next)if(n->entity&&n->entity->handle==h)return n->entity;return 0;} }
// 0x00419650 - Semantic reconstruction of the EBX-bound stage focus updater.
// The retail adapter at 0x004198A0 moves `this` from ECX into EBX before call.
int StageFocus_UpdateFade(StageFocusState* s,const StageFocusEnv* e){
 if(s->stage_id!=e->current_stage_id)s->secondary_frame=0;
 if(e->prepare)e->prepare(s,s->selected,1);
 const float cx=e->camera_x+224.0f,cy=e->camera_y+16.0f;
 for(int i=0;i<10;++i){StageFocusSlot& q=s->slots[i];StageFocusEntity* a=q.handle?Find(q.handle,e->active):0;if(!a&&q.handle)a=Find(q.handle,e->pending);if(!a){q.handle=0;continue;}if(a->suppress_focus_fade)continue;
  float dx=std::fabs(cx-q.x),dy=std::fabs(cy-q.y),hx=q.half_width*.5f,hy=a->sprite_height*a->scale_y*.5f;int base=a->base_alpha;
  if(dx<hx&&dy<hy)a->alpha=(unsigned char)(base>>2);
  else if(dx<hx+32.0f&&dy<hy)a->alpha=(unsigned char)(base-(int)((hx+32.0f-dx)*(float)((base*3)/4)*0.03125f));
  else if(dx<hx&&dy<hy+32.0f)a->alpha=(unsigned char)(base-(int)((hy+32.0f-dy)*(float)((base*3)/4)*0.03125f));
  else a->alpha=(unsigned char)base;
 }
 ++s->frame;++s->secondary_frame;return 1;
}
