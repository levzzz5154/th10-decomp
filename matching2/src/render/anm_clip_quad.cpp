#include "th10/render/anm_clip_quad.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x004462F0 - resets the clip quad to a centered 256x256 quad, mirrors it
// into the global copy, and uploads it to the vertex buffer stream.
void AnmManager_UploadClipQuad(ClipQuadHost* host,
                               ClipQuadEnv* env) {
	float* quad = host->quad;
	// 4 vertices x (x, y, z, u, v), exactly the retail constants.
	const float vertices[20] = {
	    -128.0f, -128.0f, 0.0f, 0.0f, 0.0f, // top-left
	    128.0f,  -128.0f, 0.0f, 1.0f, 0.0f, // top-right
	    -128.0f, 128.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	    128.0f,  128.0f,  0.0f, 1.0f, 1.0f, // bottom-right
	};
	std::memcpy(quad, vertices, sizeof(vertices));
	std::memcpy(env->mirror, quad, sizeof(vertices));

	env->set_device_state(env->device, 0x50, 0, 0x102);
	void* locked = 0;
	if (env->lock_buffer(host->vertex_buffer, &locked) == 0 && locked != 0) {
		std::memcpy(locked, quad, sizeof(vertices));
	}
	env->unlock_buffer(host->vertex_buffer);
	env->set_stream_source(env->device, host->vertex_buffer, 0x14);
}
