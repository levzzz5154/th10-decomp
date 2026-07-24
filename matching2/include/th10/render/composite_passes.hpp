#pragma once

// Staged composite passes, overlay globals, and fade state (retail 0x00402CA0).
// Retail function 0x00402CA0.
struct CompositeState{unsigned flags;int counter;unsigned char visibility;int overlay_enabled;unsigned end_color,state_34,state_36,state_37,snapshot[70];};struct CompositeGlobalRenderState{int alpha_blend_state,overlay_enabled;unsigned overlay_color;};struct CompositeEnv{CompositeGlobalRenderState*global;void(*flush)();void(*publish_snapshot)(const unsigned[70]);void(*setup_snapshot)();void(*set_render_state)(int,unsigned);void(*draw_staged)();void(*draw_quad)(CompositeState*);void(*tick_fade)(CompositeState*,float);};int CompositeEffect_Draw(CompositeState*,const CompositeEnv*);
