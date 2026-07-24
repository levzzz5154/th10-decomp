#pragma once

// Projected quad rebuild, billboard projection, and box culling (retail 0x00444240, 0x00443B60, 0x00403090).
// register-accurate naked x86 assembly.

struct ProjectionVec3 { float x, y, z; };
struct ProjectionMatrix { float m[16]; };

// --- 0x00444240 -------------------------------------------------------------
struct ProjectedObject {
	float rotation_x, rotation_y, rotation_z;
	float scale_x, scale_y;
	ProjectionMatrix source_matrix;
	ProjectionMatrix world_matrix;
	ProjectionVec3 base_position;
	ProjectionVec3 layer_position;
	ProjectionVec3 offset_position;
	unsigned int flags;
};
struct ProjectionContext { ProjectionMatrix last_world; };
struct ProjectedQuadEnv {
	void (*rotation_x)(ProjectionMatrix*, float);
	void (*rotation_y)(ProjectionMatrix*, float);
	void (*rotation_z)(ProjectionMatrix*, float);
	void (*multiply)(ProjectionMatrix* out, const ProjectionMatrix* left,
	                 const ProjectionMatrix* right);
	void (*project)(ProjectionVec3* out, const ProjectionVec3* in,
	                const ProjectionMatrix* world);
};
int ProjectedQuad_Update(ProjectedObject* object,
                         ProjectionContext* context,
                         ProjectionVec3 output[4], ProjectedQuadEnv* env);

// --- 0x00443B60 -------------------------------------------------------------
struct BillboardSource {
	float rotation;
	float scale_x, scale_y;
	float width, height;
	ProjectionVec3 base_position;
	ProjectionVec3 layer_position;
	ProjectionVec3 offset_position;
	unsigned int flags;
};
struct BillboardEnv {
	ProjectionVec3 reference_point;
	void (*project)(ProjectionVec3* out, const ProjectionVec3* in);
};
int Billboard_BuildProjectedQuad(const BillboardSource* source,
                                 ProjectionVec3 output[4],
                                 BillboardEnv* env);

// --- 0x00403090 -------------------------------------------------------------
struct ProjectionBox { ProjectionVec3 center; ProjectionVec3 size; };
struct ProjectionCullSource {
	ProjectionVec3 base_position;
	ProjectionVec3 position_offset;
};
struct ProjectionCullEnv {
	float screen_left, screen_right, screen_top, screen_bottom;
	void (*project)(ProjectionVec3* out, const ProjectionVec3* in,
	                const ProjectionVec3* translation);
};
int ProjectedBox_IsOutside(const ProjectionCullSource* source,
                           const ProjectionBox* box,
                           const ProjectionVec3* translation,
                           float maximum_distance_squared,
                           ProjectionCullEnv* env);
