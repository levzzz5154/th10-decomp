#pragma once

// FPS counter render and frame-rate counter update (retail 0x004135D0, 0x004134B0).
#include "th10/util/scalars.hpp"

// --- 0x004135D0 --------------------------------------------------------------
int FpsCounter_Render(void (*update_average)(void), int game_state,
                      void* game_thread, const float* fps, float low_threshold,
                      float mid_threshold, Word* overlay_color,
                      void (*print_overlay)(const float position[3],
                                            const char* format, double fps),
                      int* accumulator, int skipped_frames);

struct FrameRateCounter {
	double last_stamp;     // +0x14
	int stall_count;       // +0x1c
	int frame_count;       // +0x20
	double active_seconds; // +0x24
	double total_seconds;  // +0x2c
	float fps;             // +0x34
};

struct FrameRateEnv {
	double (*read_seconds)(void);
	double min_interval;    // minimum measurement window
	double negative_wrap;   // added when the frame counter wrapped negative
	double stall_threshold; // fps above this counts as a timer stall
	double fps_cap;         // fps at/below this is accumulated as-is
	double second_unit;     // 1.0 second
	Word* input_flags;   // pause/skip flag word, may be null
	double* sync_stamps[4];    // global resync stamps rewritten on stalls
	double* skip_accumulator;  // cleared on the second stall in a row pair
};

int FrameRateCounter_Update(FrameRateCounter* counter,
                            FrameRateEnv* env);
