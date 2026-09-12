#include "th10/render/quad_build_anchored.hpp"

// 0x00443080 - constructs the shared four-vertex quad from its transformed
// origin, scaled dimensions, and horizontal/vertical anchor modes, then sends
// it through render mode 1.
void Quad_BuildAndRenderAnchored(const AnchoredQuadSource* source,
                                 AnchoredQuadEnv* env) {
	const float origin_x = source->base_x + source->layer_x + source->offset_x;
	const float origin_y = source->base_y + source->layer_y + source->offset_y;
	const float z = source->base_z + source->layer_z + source->offset_z;
	const float width = source->width * source->scale_x;
	const float height = source->height * source->scale_y;

	float left = origin_x;
	float right = origin_x;
	if (source->anchor_x == 0) {
		left = env->round_center_edge(origin_x - width * 0.5f, width);
		right = left + width;
	} else if (source->anchor_x == 1) {
		right = left + width;
	} else if (source->anchor_x == 2) {
		left = origin_x - width;
	}

	float top = origin_y;
	float bottom = origin_y;
	if (source->anchor_y == 0) {
		top = env->round_center_edge(origin_y - height * 0.5f, height);
		bottom = top + height;
	} else if (source->anchor_y == 1) {
		bottom = top + height;
	} else if (source->anchor_y == 2) {
		top = origin_y - height;
	}

	AnchoredQuadVertex vertices[4] = {
	    {left, top, z, 1.0f}, {right, top, z, 1.0f},
	    {left, bottom, z, 1.0f}, {right, bottom, z, 1.0f},
	};
	env->render_quad(vertices, 1);
}
