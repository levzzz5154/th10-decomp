#include "th10/render/projection_quads.hpp"

#include <cmath>
#include <cstring>

namespace {
ProjectionVec3 SumPosition(const ProjectionVec3& a, const ProjectionVec3& b,
                        const ProjectionVec3& c) {
	return {a.x + b.x + c.x, a.y + b.y + c.y, a.z + b.z + c.z};
}
void AnchorOffsets(unsigned int mode, float extent, float* low, float* high) {
	if (mode == 0) { *low = -extent * 0.5f; *high = extent * 0.5f; }
	else if (mode == 1) { *low = 0.0f; *high = extent; }
	else if (mode == 2) { *low = -extent; *high = 0.0f; }
	else { *low = *high = 0.0f; }
}
}

// 0x00444240 - rebuilds the object's scaled/rotated world matrix when dirty,
// translates it by the three position layers, projects the anchor-dependent
// 256x256 quad, and publishes the exact world matrix used by projection.
int ProjectedQuad_Update(ProjectedObject* object,
                         ProjectionContext* context,
                         ProjectionVec3 output[4], ProjectedQuadEnv* env) {
	if ((object->flags & 0x4000u) == 0 && (object->flags & 0xCu) != 0) {
		object->world_matrix = object->source_matrix;
		object->world_matrix.m[0] *= object->scale_x;
		object->world_matrix.m[5] *= object->scale_y;
		object->flags &= ~8u;
		ProjectionMatrix rotation, combined;
		if (object->rotation_x != 0.0f) {
			env->rotation_x(&rotation, object->rotation_x);
			env->multiply(&combined, &object->world_matrix, &rotation);
			object->world_matrix = combined;
		}
		if (object->rotation_y != 0.0f) {
			env->rotation_y(&rotation, object->rotation_y);
			env->multiply(&combined, &object->world_matrix, &rotation);
			object->world_matrix = combined;
		}
		if (object->rotation_z != 0.0f) {
			env->rotation_z(&rotation, object->rotation_z);
			env->multiply(&combined, &object->world_matrix, &rotation);
			object->world_matrix = combined;
		}
		object->flags &= ~4u;
	}
	ProjectionMatrix world = object->world_matrix;
	ProjectionVec3 position = SumPosition(object->base_position,
	                                  object->layer_position,
	                                  object->offset_position);
	world.m[12] += position.x; world.m[13] += position.y; world.m[14] += position.z;
	float left, right, top, bottom;
	AnchorOffsets((object->flags >> 18) & 3u, 256.0f, &left, &right);
	AnchorOffsets((object->flags >> 20) & 3u, 256.0f, &top, &bottom);
	ProjectionVec3 input[4] = {{left, top, 0}, {right, top, 0},
	                        {left, bottom, 0}, {right, bottom, 0}};
	for (int i = 0; i < 4; ++i) env->project(&output[i], &input[i], &world);
	context->last_world = world;
	return 0;
}

// 0x00443B60 - projects the billboard center and camera reference, derives the
// perspective-scaled extents, applies anchor modes and in-plane rotation, and
// publishes four projected vertices. A center outside normalized depth fails.
int Billboard_BuildProjectedQuad(const BillboardSource* source,
                                 ProjectionVec3 output[4],
                                 BillboardEnv* env) {
	ProjectionVec3 center_world = SumPosition(source->base_position,
	                                      source->layer_position,
	                                      source->offset_position);
	ProjectionVec3 center, reference;
	env->project(&center, &center_world);
	if (center.z < 0.0f || center.z > 1.0f) return -1;
	env->project(&reference, &env->reference_point);
	const float dx = reference.x - center.x;
	const float dy = reference.y - center.y;
	const float dz = reference.z - center.z;
	const float perspective = std::sqrt(dx*dx + dy*dy + dz*dz) * 0.5f;
	const float width = source->width * source->scale_x * perspective;
	const float height = source->height * source->scale_y * perspective;
	float left, right, top, bottom;
	AnchorOffsets((source->flags >> 18) & 3u, width, &left, &right);
	AnchorOffsets((source->flags >> 20) & 3u, height, &top, &bottom);
	const float cosine = std::cos(source->rotation);
	const float sine = std::sin(source->rotation);
	const float xs[4] = {left, right, left, right};
	const float ys[4] = {top, top, bottom, bottom};
	for (int i = 0; i < 4; ++i) {
		output[i].x = xs[i] * cosine - ys[i] * sine + center.x;
		output[i].y = xs[i] * sine + ys[i] * cosine + center.y;
		output[i].z = center.z;
	}
	return 0;
}

// 0x00403090 - performs the retail distance precheck, projects all eight box
// corners, ignores points outside normalized depth, and tests the resulting
// screen-space bounds against the active viewport rectangle.
int ProjectedBox_IsOutside(const ProjectionCullSource* source,
                           const ProjectionBox* box,
                           const ProjectionVec3* translation,
                           float maximum_distance_squared,
                           ProjectionCullEnv* env) {
	ProjectionVec3 object_center = {source->base_position.x + source->position_offset.x,
	                             source->base_position.y + source->position_offset.y,
	                             source->base_position.z + source->position_offset.z};
	ProjectionVec3 box_center = {box->center.x + translation->x,
	                          box->center.y + translation->y,
	                          box->center.z + translation->z};
	float dx = box_center.x - object_center.x, dy = box_center.y - object_center.y,
	      dz = box_center.z - object_center.z;
	if (dx*dx + dy*dy + dz*dz > maximum_distance_squared) return 1;
	const float hx = box->size.x * 0.5f, hy = box->size.y * 0.5f,
	            hz = box->size.z * 0.5f;
	bool have_point = false;
	float min_x = 0, max_x = 0, min_y = 0, max_y = 0;
	for (int ix = -1; ix <= 1; ix += 2) for (int iy = -1; iy <= 1; iy += 2)
		for (int iz = -1; iz <= 1; iz += 2) {
			ProjectionVec3 corner = {box->center.x + ix*hx, box->center.y + iy*hy,
			                      box->center.z + iz*hz};
			ProjectionVec3 projected; env->project(&projected, &corner, translation);
			if (projected.z < 0.0f || projected.z >= 1.0f) continue;
			if (!have_point) { min_x=max_x=projected.x; min_y=max_y=projected.y; have_point=true; }
			else {
				if (projected.x < min_x) min_x = projected.x;
				if (projected.x > max_x) max_x = projected.x;
				if (projected.y < min_y) min_y = projected.y;
				if (projected.y > max_y) max_y = projected.y;
			}
		}
	if (!have_point) return 1;
	return (max_x >= env->screen_left && min_x < env->screen_right &&
	        max_y >= env->screen_top && min_y < env->screen_bottom) ? 0 : 1;
}
