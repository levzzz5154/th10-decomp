#pragma once

// DirectSound device/worker bring-up and WAV preload (retail 0x0043CD30).
//
// Retail function: 0x0043CD30 (__thiscall, 1008 bytes), the body of the
// sound worker thread entry StartAddress (0x0043CCF0). The worker receives
// the global sound context (Parameter, 0x00492590) and the game window
// (dword_4977B8) and performs the full DirectSound bring-up:
//
//   1. Clears the 128-slot secondary-buffer handle table (this+0x408,
//      memset 0xFF over 0x200 bytes) and the 12 music/stream handle
//      dwords (this[392..403]) to -1.
//   2. Allocates a 4-byte device cell (operator new), zeroes it, and
//      stores it at this[388]. Retail dereferences the cell without a
//      null check; the readable form guards the (never-taken) failure.
//   3. DirectSoundCreate8(0, cell, 0) then SetCooperativeLevel(hWnd, 2).
//      On either failure: logs "DirectSound " (aDirectsound_0 via
//      0x0044B810), releases and frees the cell, and returns -1.
//   4. Sets the primary buffer format to 16-bit / 2 channels / 44100 Hz
//      via 0x0044C7E0; the result is ignored (retail behavior).
//   5. Copies the raw device pointer into this[0], zeroes the stream
//      cursor this[390], and creates the 0x8000-byte streaming buffer
//      (DSBUFFERDESC dwSize 36, dwFlags 32776, WAVEFORMATEX
//      {tag 1, ch 2, rate 44100, avg 176400, align 4, bits 16}) into
//      this+386 (vtable +12), locks it (vtable +44), zero-fills the
//      0x8000-byte region, unlocks (vtable +76), and plays it looping
//      (vtable +48 with flags 1).
//   6. Sets both volume words this[5297]/this[5298] to 100, arms a
//      250 ms window timer (SetTimer(hWnd, 0, 0xFA, 0)), and stores the
//      window at this[387].
//   7. Preloads the 37 retail WAVs (filename table off_474B40) through
//      0x0043D390 (recovered as SoundWave_LoadPending) while the
//      shutdown word dword_4977B4 stays != 2. A load failure logs
//      "error : Sound %s" with the filename and returns -1; finishing
//      all 37 logs "DirectSound " (aDirectsound) and returns 0; a
//      shutdown request mid-preload returns -1.
//
// Every COM/Win32 edge (DirectSoundCreate8, the four buffer vtable
// slots, SetTimer, the debug log 0x0044B810, the WAV loader) is injected
// through SoundInitEnv so host-side tests can drive each branch
// deterministically.


// WAVEFORMATEX image used for both the primary format request and the
// streaming buffer description.
struct SoundInitWaveFormat {
	unsigned short tag;        // wFormatTag, retail 1 (PCM)
	unsigned short channels;   // nChannels, retail 2
	unsigned int rate;         // nSamplesPerSec, retail 44100
	unsigned int avg_bytes;    // nAvgBytesPerSec, retail 176400
	unsigned short block_align; // nBlockAlign, retail 4
	unsigned short bits;       // wBitsPerSample, retail 16
	unsigned short cb_size;    // cbSize, retail 0
};

// DSBUFFERDESC image for the streaming buffer (retail stack block at
// ebp-0x28: dwSize 36, dwFlags 32776, dwBufferBytes 0x8000).
struct SoundInitBufferDesc {
	unsigned int size;      // dwSize, retail 36
	unsigned int flags;     // dwFlags, retail 32776
	unsigned int bytes;     // dwBufferBytes, retail 0x8000
	unsigned int reserved;  // dwReserved, retail 0
	const SoundInitWaveFormat* format;
};

// Readable slice of the retail sound context (Parameter, 0x00492590).
// Retail dword indices are given for each field.
struct SoundDevice {
	void* device;                // this[0], raw IDirectSound8*
	int buffer_handles[128];     // this[258..385], memset to -1
	void* stream_buffer;         // this[386], streaming secondary buffer
	void* window;                // this[387], HWND stored after timer arm
	void** device_cell;          // this[388], heap cell owning the device
	int stream_cursor;           // this[390], zeroed during bring-up
	int music_handles[12];       // this[392..403], set to -1
	int volume_a;                // this[5297], set to 100
	int volume_b;                // this[5298], set to 100
};

// Injected COM/Win32 edges for 0x0043CD30.
struct SoundInitEnv {
	// operator new(4): returns a zeroed one-pointer cell, or null.
	void** (*allocate_cell)();
	// j__free on the device cell.
	void (*free_cell)(void** cell);
	// IUnknown::Release (vtable +8) on a device interface.
	void (*release_device)(void* device);
	// DirectSoundCreate8(0, cell, 0); fills *cell on success.
	int (*create_device)(void** cell);
	// IDirectSound8::SetCooperativeLevel (vtable +24); retail level 2.
	int (*set_cooperative_level)(void* device, void* window, int level);
	// 0x0044C7E0: set the primary buffer format (bits, channels, rate).
	int (*set_primary_format)(int bits, int channels, int rate,
	                          void** cell);
	// IDirectSound8::CreateSoundBuffer (vtable +12).
	int (*create_buffer)(void* device, const SoundInitBufferDesc* desc,
	                     void** buffer_out);
	// IDirectSoundBuffer::Lock (vtable +44).
	int (*lock_buffer)(void* buffer, unsigned int offset,
	                   unsigned int bytes, void** region1,
	                   unsigned int* length1, void** region2,
	                   unsigned int* length2, unsigned int flags);
	// IDirectSoundBuffer::Unlock (vtable +76).
	void (*unlock_buffer)(void* buffer, void* region1,
	                      unsigned int length1, void* region2,
	                      unsigned int length2);
	// IDirectSoundBuffer::Play (vtable +48); retail (0, 0, 1) looping.
	void (*play_buffer)(void* buffer, int reserved1, int reserved2,
	                    int flags);
	// SetTimer(window, id, milliseconds, 0); retail (hWnd, 0, 250).
	void (*set_timer)(void* window, unsigned int timer_id,
	                  unsigned int milliseconds);
	// 0x0044B810 debug log; argument is null for the plain
	// "DirectSound " messages and the filename for "error : Sound %s".
	void (*log)(const char* message, const char* argument);
	// 0x0043D390 (SoundWave_LoadPending path): nonzero on failure.
	int (*load_wave)(int index, const char* filename);
	// off_474B40: the 37 retail WAV filenames.
	const char* const* filenames;
	// dword_4977B4: worker shutdown word; 2 aborts the preload.
	const volatile int* shutdown_flag;
};

// Retail log strings (0x0044B810 arguments in 0x0043CD30).
extern const char kSoundInitLogDirectSoundError[]; // aDirectsound_0
extern const char kSoundInitLogDirectSoundReady[]; // aDirectsound
extern const char kSoundInitLogSoundError[];       // aErrorSound

// 0x0043CD30 - Bring up the DirectSound device, streaming buffer, and
// WAV preload for the sound worker thread. Returns 0 on full success
// and -1 on any failure or on a shutdown request during the preload.
int SoundDevice_InitializeWorker(SoundDevice* device, void* window,
                                 const SoundInitEnv* env);
