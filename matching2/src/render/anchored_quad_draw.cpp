#include "th10/render/anchored_quad_draw.hpp"
namespace th10::render {
// Semantic reconstruction of retail 0x00443290. IDA confirms the sprite descriptor in EAX.
Quad BuildAnchoredQuad(const AnchoredQuad&s){float w=s.width*s.scale_x,h=s.height*s.scale_y;float x=s.position[0]+s.offset[0]+s.parent[0],y=s.position[1]+s.offset[1]+s.parent[1],z=s.position[2]+s.offset[2]+s.parent[2];auto axis=[](float p,float d,unsigned a){return a==0?p-d*.5f:a==1?p:p-d;};float l=axis(x,w,(s.flags>>18)&3),r=l+w,t=axis(y,h,(s.flags>>20)&3),b=t+h;return{{Vertex{l,t,z},Vertex{r,t,z},Vertex{r,b,z},Vertex{l,b,z}}};}
}
