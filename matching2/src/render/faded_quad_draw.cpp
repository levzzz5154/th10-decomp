#include "th10/render/faded_quad_draw.hpp"
#include "th10/render/projection_quads.hpp"

#include <cmath>

namespace {
unsigned char FadeChannel(unsigned char base, unsigned char target, float factor) {
	int delta = (int)base - (int)target;
	int value = (int)base - (int)std::lround(delta * factor);
	if (value < 0) value = 0;
	if (value > 255) value = 255;
	return (unsigned char)value;
}
unsigned int FadeColor(unsigned int base, unsigned int target, float factor) {
	return (base & 0xFF000000u) |
	       FadeChannel((unsigned char)base, (unsigned char)target, factor) |
	       ((unsigned)FadeChannel((unsigned char)(base>>8),(unsigned char)(target>>8),factor)<<8) |
	       ((unsigned)FadeChannel((unsigned char)(base>>16),(unsigned char)(target>>16),factor)<<16);
}
}

// 0x004445C0 - updates the projected quad, transforms four fade probes through
// the published world matrix, attenuates RGB by camera distance while keeping
// alpha, renders mode 2, and restores all four RHW values to one.
void FadedProjectedQuad_Draw(FadeQuad* quad, FadeQuadEnv* env) {
	ProjectionVec3 projected[4];
	ProjectedQuad_Update(&quad->projection, env->projection_context, projected,
	                     env->project_env);
	unsigned int base = (quad->projection.flags & 0x8000u)
	                        ? quad->alternate_color : quad->primary_color;
	FadeColorVertex vertices[4];
	const float denominator = env->near_distance - env->far_distance;
	for (int i=0;i<4;++i) {
		ProjectionVec3 probe; env->transform(&probe,&env->source_points[i],
		                                  &env->projection_context->last_world);
		float dx=probe.x-env->camera_position.x,dy=probe.y-env->camera_position.y,
		      dz=probe.z-env->camera_position.z;
		float distance=std::sqrt(dx*dx+dy*dy+dz*dz);
		unsigned int color=base;
		if (distance>env->near_distance) {
			float factor=(env->near_distance-distance)/denominator;
			color = factor >= 1.0f ? ((env->far_color&0x00FFFFFFu)|(base&0xFF000000u))
			                       : FadeColor(base,env->far_color,factor);
		}
		vertices[i]={projected[i],color,1.0f};
	}
	env->render(vertices,2);
	for(int i=0;i<4;++i) vertices[i].rhw=1.0f;
}
