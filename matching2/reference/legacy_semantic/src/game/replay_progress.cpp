#include "th10/game/replay_progress.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


#include <cmath>
#include <cstring>

namespace {


void RegisterClock(RegisteredClock* clock, float* frame_scale) {
	if ((clock->flags & 1u) == 0) {
		clock->clock.frame = 0;
		clock->clock.previous = (int)0xFFF0BDC1u;
		clock->clock.timer = 0.0f;
		clock->clock.control = frame_scale;
		clock->flags |= 1u;
	}
}



} // namespace

// 0x00415DB0 - Load one stage entry out of a replay archive. The stage
// payload lives at the offset stored in the archive's entry table (8-byte
// entries, offset at +4). A fresh 0x90-byte node is constructed over the
// payload, remembered as the current stage node, and tagged with its index;
// switching to a different stage number resets the global frame counter.
void* ReplayStage_LoadEntry(char* archive, int index, void** current_slot,
                            void* (*allocate)(unsigned int size),
                            void* (*construct)(void* memory, void* payload),
                            int* stage_slot, int* frame_slot) {
	void* node = allocate(0x90);
	if (node != 0) {
		int offset = *(int*)(archive + 4 + index * 8);
		node = construct(node, archive + offset);
	}
	*current_slot = node;
	*(int*)node = index;
	if (*stage_slot != index + 1) {
		*frame_slot = 0;
	}
	*stage_slot = index + 1;
	return node;
}

// 0x00412FF0 - advances the replay timer and clamps it to its final frame
// (0x82) once the advance overshoots the end of the replay.
void ReplayTimer_ClampToEnd(RegisteredClock* clock, float amount,
                            void (*advance)(float amount),
                            float* frame_scale) {
	if (clock->clock.frame < 0x82) {
		advance(amount);
		if (clock->clock.frame > 0x82) {
			RegisterClock(clock, frame_scale);
			clock->clock.frame = 0x82;
			clock->clock.timer = 130.0f;
			clock->clock.previous = 0x81;
		}
	}
}
