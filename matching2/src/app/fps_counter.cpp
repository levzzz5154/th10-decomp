#include "th10/app/fps_counter.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>


// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x004135D0 - FPS counter draw callback: refresh the rolling average, and
// unless the game is in state 0xE (shutdown) or the game thread is gone,
// print "%2.1ffps" tinted by the frame rate (red below the low threshold,
// pink below the mid threshold, white otherwise), restoring white after.
// The frame accumulator then absorbs the skipped-frame count plus one.
int FpsCounter_Render(void (*update_average)(void), int game_state,
                      void* game_thread, float fps, float low_threshold,
                      float mid_threshold, Word* overlay_color,
                      void (*print_overlay)(const char* format),
                      int* accumulator, int skipped_frames) {
	update_average();
	if (game_state != 0xE && game_thread != 0) {
		Word color;
		if (fps < low_threshold) {
			color = 0xFF5050FF;
		} else if (fps < mid_threshold) {
			color = 0xFFA0A0FF;
		} else {
			color = 0xFFFFFFFF;
		}
		*overlay_color = color;
		print_overlay("%2.1ffps");
		*overlay_color = 0xFFFFFFFF;
	}
	*accumulator += skipped_frames + 1;
	return 1;
}

// 0x004134B0 - frame-rate counter update: measures fps over the elapsed
// window, resynchronizes the global frame stamps after repeated timer
// stalls, and accumulates played time while the game is not paused/skipping.

int FrameRateCounter_Update(FrameRateCounter* counter,
                            FrameRateEnv* env) {
	double now = env->read_seconds();
	if (now < counter->last_stamp) counter->last_stamp = now;
	double delta = now - counter->last_stamp;
	if (delta < env->min_interval) return 1;
	counter->last_stamp += delta;

	double frames = (double)counter->frame_count;
	if (counter->frame_count < 0) frames += env->negative_wrap;
	counter->fps = (float)(frames / delta);

	if (env->stall_threshold < frames / delta) {
		counter->stall_count += 1;
		if (counter->stall_count == 2) {
			double stamp = env->read_seconds();
			for (int i = 0; i < 4; ++i) *env->sync_stamps[i] = stamp;
		} else if (counter->stall_count == 4) {
			*env->skip_accumulator = 0.0;
			double stamp = env->read_seconds();
			for (int i = 0; i < 4; ++i) *env->sync_stamps[i] = stamp;
			counter->stall_count = 0;
		}
	} else {
		counter->stall_count = 0;
	}

	if (env->input_flags != 0) {
		if ((*env->input_flags & 0x14) == 0) {
			counter->total_seconds += env->second_unit;
			if ((double)counter->fps <= env->fps_cap) {
				counter->active_seconds += (double)counter->fps;
			} else {
				counter->active_seconds += env->second_unit;
			}
		}
		*env->input_flags &= ~0x80u;
	}
	counter->frame_count = 0;
	return 1;
}
