#pragma once

// Common sound-effect buffer initialization (retail 0x0043DB60).
#include "th10/util/scalars.hpp"

struct SoundEffectSpec {
	int source_index; // wave bank buffer to duplicate
	short pan;        // initial pan applied to the duplicate
};

struct SoundManager {
	void* device;        // null disables buffer duplication
	void** wave_buffers; // decoded wave-bank buffers
	void** duplicated;   // per-effect duplicated buffers
	int loaded;          // wave bank load result flag
	int queue_ids[12];   // pending-event queue, reset to -1
	int bgm_enabled;     // copied from config
	int bgm_use_stream;  // copied from config
	int bgm_start_offset;
};

struct SoundBufferEnv {
	int (*load_wave_bank)(SoundManager* manager);
	void (*duplicate_buffer)(void* device, void* source, void** out);
	void (*set_volume)(void* buffer, int volume);
	void (*set_pan)(void* buffer, int pan);
	const SoundEffectSpec* specs;
	int spec_count;
	Byte bgm_enabled_flag;
	Byte bgm_stream_flag;
	long long (*read_clock)(void);
};

int SoundManager_InitCommonBuffers(SoundManager* manager,
                                   SoundBufferEnv* env);
