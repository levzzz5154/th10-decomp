#include "th10/platform/sound_event_queue.hpp"
#include "th10/game/player_motion.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// 0x0043DD10 - Queue a sound event into one of twelve per-frame slots. A
// new sound claims the first free slot (id < 0), records its priority in
// the volume table, and stamps entry zero; a repeated sound appends another
// stamp to its slot until the 0x80-entry ring is full.
void SoundQueue_QueueEvent(int* slot_ids, int* slot_counts,
                           int (*slot_stamps)[128], int* volume_table,
                           int sound_id, short priority, int stamp) {
	for (int index = 0; index < 12; ++index) {
		if (slot_ids[index] < 0) {
			slot_ids[index] = sound_id;
			volume_table[sound_id] = priority;
			slot_stamps[index][0] = stamp;
			slot_counts[index] += 1;
			return;
		}
		if (slot_ids[index] == sound_id) {
			int count = slot_counts[index];
			if (count > 0x7F) return;
			slot_stamps[index][count] = stamp;
			slot_counts[index] += 1;
			return;
		}
	}
}
