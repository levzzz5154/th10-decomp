#pragma once

// Anchored four-vertex quad construction and render dispatch (retail 0x00443080).
// --- 0x00443080 -------------------------------------------------------------
struct AnchoredQuadVec3 { float x, y, z; };
struct AnchoredQuadVertex { float x, y, z, w; };
struct AnchoredQuadSource {
	float base_x, base_y, base_z;
	float layer_x, layer_y, layer_z;
	float offset_x, offset_y, offset_z;
	float scale_x, scale_y;
	float width, height;
	unsigned int anchor_x; // 0=center, 1=left, 2=right
	unsigned int anchor_y; // 0=center, 1=top, 2=bottom
};
struct AnchoredQuadEnv {
	float (*round_center_edge)(float edge, float extent);
	void (*render_quad)(const AnchoredQuadVertex vertices[4], int mode);
};
void Quad_BuildAndRenderAnchored(const AnchoredQuadSource* source,
                                 AnchoredQuadEnv* env);
