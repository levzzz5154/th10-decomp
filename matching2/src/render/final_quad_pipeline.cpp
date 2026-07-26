#include "th10/render/final_quad_pipeline.hpp"
#include <algorithm>
#include <cmath>
namespace th10::render_final {
// Semantic reconstruction of retail 0x00442670.
QuadResult DrawQuad(const QuadInput&i){QuadResult o;o.v=i.v;for(auto&v:o.v){v.x+=i.offset_x;v.y+=i.offset_y;if(i.snap){v.x=std::round(v.x)-.5f;v.y=std::round(v.y)-.5f;}if(i.override_color)v.color=i.color;}float loX=o.v[0].x,hiX=loX,loY=o.v[0].y,hiY=loY;for(auto&v:o.v){loX=std::min(loX,v.x);hiX=std::max(hiX,v.x);loY=std::min(loY,v.y);hiY=std::max(hiY,v.y);}o.visible=hiX>=i.viewport_x&&hiY>=i.viewport_y&&loX<=i.viewport_x+i.viewport_w&&loY<=i.viewport_y+i.viewport_h;o.texture_changed=o.visible;o.state_changed=o.visible;return o;}
}
