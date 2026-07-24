#pragma once

// Projected quad draw with camera-distance RGB attenuation (retail 0x004445C0).
#include "th10/render/projection_quads.hpp"

struct FadeColorVertex { ProjectionVec3 position; unsigned int color; float rhw; };
struct FadeQuad {
	ProjectedObject projection;
	unsigned int primary_color;
	unsigned int alternate_color;
};
struct FadeQuadEnv {
	ProjectionContext* projection_context;
	ProjectedQuadEnv* project_env;
	ProjectionVec3 camera_position;
	float near_distance;
	float far_distance;
	unsigned int far_color;
	ProjectionVec3 source_points[4];
	void (*transform)(ProjectionVec3* out, const ProjectionVec3* in,
	                  const ProjectionMatrix* matrix);
	void (*render)(FadeColorVertex vertices[4], int mode);
};
void FadedProjectedQuad_Draw(FadeQuad* quad, FadeQuadEnv* env);
