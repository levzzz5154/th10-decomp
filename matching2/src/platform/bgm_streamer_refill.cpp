#include "th10/platform/bgm_streamer_refill.hpp"
#include "th10/game/ending_text.hpp"
#include "th10/render/effect_ring_update.hpp"

#include <cmath>
#include <cstring>

namespace {

} // namespace

// 0x0044D850 - Refill one notify segment of the streaming BGM buffer: bail
// while the play cursor still sits inside the segment about to be rewritten,
// poll the restore chain (a lost-and-restored buffer forces a full rewrite
// through the 0x0044D110 path), lock exactly one segment, fill it with
// decoded PCM or with silence once the reader is exhausted, unlock, account
// for play-cursor progress with buffer wraparound, stop the buffer after the
// silent tail has fully played out, and advance the write offset modulo the
// buffer size.
int Streamer_RefillSegment(StreamerState* state,
                           const StreamerEnv* env) {
	if (state->has_buffer == 0 || state->has_reader == 0) {
		return (int)kStreamerNotReady;
	}

	unsigned int play_cursor = 0;
	env->get_play_cursor(env->context, &play_cursor);
	// Unsigned wrap on (play - segment) is intended: the segment about to be
	// written must not contain the play cursor.
	if (play_cursor - state->segment_bytes <= state->write_offset &&
	    state->write_offset < play_cursor) {
		return (int)kStreamerNotReady;
	}

	int restored = 0;
	int status = env->prime_buffers(env->context, &restored);
	if (status < 0) {
		return status;
	}
	if (restored != 0) {
		status = env->full_refill(env->context);
		return status < 0 ? status : 0;
	}

	unsigned char* pcm = 0;
	unsigned int locked_bytes = 0;
	void* wrap_pcm = 0;
	status = env->lock_segment(env->context, state->write_offset,
	                           state->segment_bytes, &pcm, &locked_bytes,
	                           &wrap_pcm);
	if (status < 0) {
		return status;
	}
	if (wrap_pcm != 0) {
		return (int)kStreamerUnexpected;
	}

	if (state->end_of_stream == 0) {
		status = env->read_pcm(env->context, pcm, locked_bytes);
		if (status < 0) {
			// Mirrors the raw early-out: the decode error is reported
			// without touching the progress accounting.
			return status;
		}
	} else {
		// Feed silence until the tail drains; 8-bit PCM silence is the
		// unsigned midpoint 0x80, wider formats use zero.
		unsigned char silence =
			state->bits_per_sample == 8 ? (unsigned char)0x80
			                            : (unsigned char)0;
		std::memset(pcm, silence, locked_bytes);
	}
	env->unlock_segment(env->context, pcm, locked_bytes);

	env->get_play_cursor(env->context, &play_cursor);
	unsigned int advanced =
		play_cursor < state->last_play_cursor
			? state->buffer_bytes - state->last_play_cursor + play_cursor
			: play_cursor - state->last_play_cursor;
	state->total_streamed += advanced;
	state->last_play_cursor = play_cursor;

	if (state->end_of_stream != 0 &&
	    state->total_pcm_bytes <= state->total_streamed) {
		env->stop_buffer(env->context);
	}
	state->write_offset =
		(state->write_offset + locked_bytes) % state->buffer_bytes;
	return 0;
}
