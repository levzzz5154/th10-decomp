// Historical environment-based approximation. The complete layout-faithful
// candidate and retail tests are documented in
// reference/recovery_notes/sound_device_init_0043cd30.md.
#include "th10/platform/sound_device_init.hpp"

#include <cstring>

// Retail addresses 0x00474AF4 (aDirectsound_0), 0x00474AE8
// (aDirectsound), and 0x00474B14 (aErrorSound). Both DirectSound log
// strings are the identical text "DirectSound "; the logger 0x0044B810
// appends them to the debug log on the failure and success paths.
const char kSoundInitLogDirectSoundError[] = "DirectSound ";
const char kSoundInitLogDirectSoundReady[] = "DirectSound ";
const char kSoundInitLogSoundError[] = "error : Sound ";

namespace {

// Number of preloaded WAV entries in off_474B40 (retail loop bound 37).
const int kPreloadCount = 37;

// Streaming buffer byte size (retail 0x8000).
const unsigned int kStreamBytes = 0x8000u;

// Teardown used by the device-creation failure path: release the device
// held by the cell, free the cell, and clear the context slot.
void ReleaseDeviceCell(SoundDevice* device,
                       const SoundInitEnv* env) {
	void** cell = device->device_cell;
	if (cell) {
		if (*cell) {
			env->release_device(*cell);
			*cell = 0;
		}
		env->free_cell(cell);
		device->device_cell = 0;
	}
}

} // namespace

// 0x0043CD30 - Sound worker initialization: DirectSound device creation,
// primary format, streaming buffer bring-up, and the 37-file WAV preload.
int SoundDevice_InitializeWorker(SoundDevice* device, void* window,
                                 const SoundInitEnv* env) {
	// memset(this + 258, 0xFF, 0x200): the 128 secondary-buffer handles.
	for (int i = 0; i < 128; ++i)
		device->buffer_handles[i] = -1;
	// this[392..403] = -1: the music/stream handle dwords.
	for (int i = 0; i < 12; ++i)
		device->music_handles[i] = -1;

	// operator new(4), zero-initialized, stored at this[388]. Retail
	// dereferences the cell without a null check (operator new never
	// fails in practice); the readable form guards the dead branch.
	void** cell = env->allocate_cell();
	device->device_cell = cell;
	if (cell && *cell) {
		// Defensive release of a previously held interface. The cell is
		// freshly zeroed, so this branch is dead in retail as well; it is
		// kept for fidelity with the decompiled body.
		env->release_device(*cell);
		*cell = 0;
	}

	// DirectSoundCreate8(0, cell, 0) then SetCooperativeLevel(hWnd, 2).
	if (env->create_device(cell) < 0 ||
	    env->set_cooperative_level(*cell, window, 2) < 0) {
		env->log(kSoundInitLogDirectSoundError, 0);
		ReleaseDeviceCell(device, env);
		return -1;
	}

	// 0x0044C7E0: primary format 16-bit / stereo / 44100 Hz. Retail
	// ignores the result (a format failure is non-fatal).
	env->set_primary_format(16, 2, 44100, cell);

	// this[0] = raw device pointer; this[390] = 0.
	device->device = *cell;
	device->stream_cursor = 0;

	// DSBUFFERDESC {36, 32776, 0x8000} with WAVEFORMATEX
	// {PCM, 2ch, 44100 Hz, 176400 B/s, align 4, 16-bit, cbSize 0}.
	SoundInitWaveFormat format;
	format.tag = 1;
	format.channels = 2;
	format.rate = 44100;
	format.avg_bytes = 176400;
	format.block_align = 4;
	format.bits = 16;
	format.cb_size = 0;
	SoundInitBufferDesc desc;
	desc.size = 36;
	desc.flags = 32776;
	desc.bytes = kStreamBytes;
	desc.reserved = 0;
	desc.format = &format;

	void* region1 = 0;
	void* region2 = 0;
	unsigned int length1 = 0;
	unsigned int length2 = 0;
	if (env->create_buffer(device->device, &desc,
	                       &device->stream_buffer) < 0 ||
	    env->lock_buffer(device->stream_buffer, 0, kStreamBytes, &region1,
	                     &length1, &region2, &length2, 0) < 0) {
		// Retail falls through to the shared -1 exit without further
		// cleanup; the worker thread reports failure and idles.
		return -1;
	}

	// Zero the locked region (retail memset over the fixed 0x8000 bytes),
	// hand it back, and start the looping stream (Play flags 1).
	std::memset(region1, 0, kStreamBytes);
	env->unlock_buffer(device->stream_buffer, region1, length1, region2,
	                   length2);
	env->play_buffer(device->stream_buffer, 0, 0, 1);

	// this[5297] = this[5298] = 100; SetTimer(hWnd, 0, 0xFA, 0);
	// this[387] = hWnd.
	device->volume_a = 100;
	device->volume_b = 100;
	env->set_timer(window, 0, 250);
	device->window = window;

	// Preload the 37 retail WAVs while no shutdown is requested
	// (dword_4977B4 != 2). The shutdown word is polled before each load.
	int index = 0;
	while (*env->shutdown_flag != 2) {
		if (env->load_wave(index, env->filenames[index])) {
			env->log(kSoundInitLogSoundError, env->filenames[index]);
			return -1;
		}
		if (++index >= kPreloadCount) {
			env->log(kSoundInitLogDirectSoundReady, 0);
			return 0;
		}
	}
	// Shutdown requested mid-preload.
	return -1;
}
