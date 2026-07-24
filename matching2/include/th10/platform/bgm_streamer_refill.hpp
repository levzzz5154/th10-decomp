#pragma once

// Streaming BGM notify-segment refill (retail 0x0044D850).
// ---------------------------------------------------------------------------
// 0x0044D850 - streaming BGM segment refill (sound worker thread 0x0043E3A0
// calls this each time the position-notify event fires)
// ---------------------------------------------------------------------------

const unsigned int kStreamerNotReady = 0x800401F0u;   // also the busy code
const unsigned int kStreamerUnexpected = 0x8000FFFFu; // wrapped lock region

struct StreamerState {
	int has_buffer;                // **(streamer+0x04) != 0 in the exe
	unsigned int buffer_bytes;     // +0x08 (full secondary-buffer size)
	int has_reader;                // *(streamer+0x0C) != 0 in the exe
	unsigned int last_play_cursor; // +0x5C
	unsigned int total_streamed;   // +0x60
	unsigned int write_offset;     // +0x64
	int end_of_stream;             // +0x68
	unsigned int segment_bytes;    // +0x6C
	unsigned int total_pcm_bytes;  // reader +0x2C
	unsigned int bits_per_sample;  // reader format +0x2E
};

struct StreamerEnv {
	void* context;
	// IDirectSoundBuffer::GetCurrentPosition (vtable +0x10)
	int (*get_play_cursor)(void* context, unsigned int* play_cursor);
	// hook 0x0044D300: restore-poll of the buffer chain; *restored reports a
	// lost-and-restored buffer that needs a full rewrite.
	int (*prime_buffers)(void* context, int* restored);
	// hook 0x0044D110 (Streamer_FillBuffer): rewrite the whole buffer.
	int (*full_refill)(void* context);
	// IDirectSoundBuffer::Lock (vtable +0x2C); *wrap_pcm receives the second
	// region pointer, which this per-segment refill never expects to be set.
	int (*lock_segment)(void* context, unsigned int offset, unsigned int bytes,
	                    unsigned char** pcm, unsigned int* locked_bytes,
	                    void** wrap_pcm);
	// hook 0x0044DE10: decode PCM from the archive cursor into the segment.
	int (*read_pcm)(void* context, unsigned char* pcm, unsigned int bytes);
	// IDirectSoundBuffer::Unlock (vtable +0x4C)
	void (*unlock_segment)(void* context, unsigned char* pcm,
	                       unsigned int locked_bytes);
	// IDirectSoundBuffer::Stop (vtable +0x48)
	void (*stop_buffer)(void* context);
};

int Streamer_RefillSegment(StreamerState* state,
                           const StreamerEnv* env);
