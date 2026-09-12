#pragma once

// Typed ANM record walk with projected-box culling (retail 0x00403A30).
#include "th10/render/projection_quads.hpp"

struct AnmRecordVm {
	unsigned int flags;
	ProjectionVec3 position;
	float scale_x, scale_y;
	float resource_width, resource_height;
};
struct AnmRecordSlot {
	short id;
	AnmRecordVm* vm;
	ProjectionVec3 offset;
	float desired_width, desired_height;
};
struct AnmRecord {
	short id;
	char type;
	unsigned char flags;
	ProjectionBox box;
	ProjectionVec3 translation;
	AnmRecordSlot* slots;
	int slot_count;
};
struct AnmRecordWalkState {
	AnmRecord** records;
	int record_count;
	ProjectionCullSource* cull_source;
	float maximum_distance_squared;
	int rejected_count;
	int accepted_count;
	int drawn_vm_count;
};
struct AnmRecordWalkEnv {
	ProjectionCullEnv* cull_env;
	void (*set_special_render_state)(bool enabled);
	void (*draw_vm)(AnmRecordVm* vm);
};
int AnmRecordTable_DrawVisible(AnmRecordWalkState* state, int required_type,
                               AnmRecordWalkEnv* env);
