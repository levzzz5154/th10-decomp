#include "th10/game/game_state_overlay_draw.hpp"
namespace { void Anim(const GameStateOverlayEnv* e,void* p){e->draw_animation(p);} void Rect(const GameStateOverlayEnv* e,float l,float t,float r,float b,unsigned c){OverlayRect x={l,t,r,b};e->draw_rect(x,c);} }
// 0x00415800 - Semantic reconstruction of the complete state overlay pass.
int GameStateOverlay_Draw(const GameStateOverlay* s,const GameStateOverlayEnv* e){
    for(int i=0;i<10;++i){Anim(e,s->primary[i]);Anim(e,s->secondary[i]);}
    for(int i=0;i<9;++i)Anim(e,s->tertiary[i]);
    for(int i=0;i<4;++i)Anim(e,s->quaternary[i]);
    for(int i=0;i<7;++i)Anim(e,s->quinary[i]);
    if(e->overlay_counter){unsigned a=(unsigned)s->overlay_alpha<<24;float edge=e->overlay_counter*0.2923077f+51.0f;Rect(e,51,461,edge,463,a);Rect(e,50,460,edge-1,462,a|0xffffffu);}
    if(s->gauge_value>0.0f){float edge=s->gauge_value*342.0f+41.0f;Rect(e,41,23,edge,25,0xff000000u);Rect(e,40,22,edge-1,24,0xffffffffu);for(int i=0;i<4;++i)if(s->gauge_segments[i].value!=0.0f){float v=s->gauge_segments[i].value<s->gauge_value?s->gauge_segments[i].value:s->gauge_value;Rect(e,40,22,v*342.0f+40.0f,24,s->gauge_segments[i].color);}}
    if(e->input_owner_present){if(e->input_device_present&&(e->input_bits&0x11u)==0)Anim(e,s->input_prompt);if(s->stage_index>=0&&e->input_device_present&&!s->prompt_hidden){Anim(e,s->late_pair[0]);Anim(e,s->late_pair[1]);}}
    return 1;
}
