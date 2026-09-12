#include "th10/platform/sound_effect_buffers.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/render/anm_vm_draw_dispatch.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x0043DB60 - sound manager common effect-buffer setup: resets the pending
// event queue, loads the wave bank, duplicates each effect buffer with its
// initial volume/pan, and derives the BGM start offset from the config.
int SoundManager_InitCommonBuffers(SoundManager* manager,
                                   SoundBufferEnv* env) {
	for (int i = 0; i < 12; ++i) manager->queue_ids[i] = -1;
	env->load_wave_bank(manager);
	if (manager->loaded == 0) return -1;
	if (manager->device != 0) {
		for (int i = 0; i < env->spec_count; ++i) {
			env->duplicate_buffer(manager->device,
			                      manager->wave_buffers[env->specs[i].source_index],
			                      &manager->duplicated[i]);
			env->set_volume(manager->duplicated[i], 0);
			env->set_pan(manager->duplicated[i], env->specs[i].pan);
		}
		manager->bgm_enabled = env->bgm_enabled_flag;
		manager->bgm_use_stream = env->bgm_stream_flag;
		if (manager->bgm_use_stream != 0) {
			manager->bgm_start_offset = -5000 - (int)env->read_clock();
		} else {
			manager->bgm_start_offset = -10000;
		}
	}
	return 0;
}

namespace {



} // namespace
