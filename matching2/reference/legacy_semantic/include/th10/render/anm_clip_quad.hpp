#pragma once

// Clip-quad upload through the ANM manager (retail 0x004462F0).
#include "th10/util/scalars.hpp"

struct ClipQuadHost {
	void* vertex_buffer;
	float quad[20]; // 4 vertices x (x, y, z, u, v)
};

struct ClipQuadEnv {
	float* mirror; // global copy of the 20 floats
	void* device;
	void (*set_device_state)(void* device, Word a, Word b,
	                         Word c);
	int (*lock_buffer)(void* vertex_buffer, void** pointer_out);
	void (*unlock_buffer)(void* vertex_buffer);
	void (*set_stream_source)(void* device, void* vertex_buffer, int stride);
};

void AnmManager_UploadClipQuad(ClipQuadHost* host,
                               ClipQuadEnv* env);
