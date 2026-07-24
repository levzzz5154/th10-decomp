#include "th10/game/stage_background.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x0040C3C0 - Rebind one stage background texture. Retail copies the
// requested name into the shared name scratch (retail 0x00497C38, first
// byte cleared before the copy), mounts the texture through the shared
// state manager in bank slot_index + 0x1D, stores the handle in the
// per-slot table (+0x80), clears busy-flag bit 2, releases the previous
// handle's object tree (retail 0x00409E50), and clears the game thread's
// pending-rebind word (+0x89A4).
int StageBackground_RebindTexture(const char* source_name, char* name_buffer,
                                  int slot_index, void** slot_table,
                                  unsigned int* busy_flags,
                                  void* state_manager,
                                  void* (*mount_texture)(int bank, void* state,
                                                         const char* name),
                                  void* previous_handle,
                                  void (*release_previous)(void* handle),
                                  int* thread_pending_word) {
    name_buffer[0] = '\0';
    int index = 0;
    do {
        name_buffer[index] = source_name[index];
    } while (source_name[index++] != '\0');
    void* handle = mount_texture(slot_index + 0x1D, state_manager, name_buffer);
    slot_table[slot_index] = handle;
    *busy_flags = *busy_flags & 0xFFFFFFFBu;
    if (release_previous != 0) release_previous(previous_handle);
    *thread_pending_word = 0;
    return 0;
}

// 0x00427960 - keeps a background item glued to its scroll anchor. When the
// scroll is locked the anchor is rewritten from the camera-relative offset
// and the trailing random offset pairs are rerolled.
void StageBackground_SyncScroll(ScrollItem* item,
                                ScrollEnv* env) {
	ScrollStage* stage = env->stage;
	int mode = stage->scroll_locked;
	ScrollAnchor* anchor = &stage->anchors[item->index];

	item->x = anchor->x;
	item->y = anchor->y;

	if (mode == 0) {
		item->rel_x = anchor->x - stage->camera_x;
		item->rel_y = anchor->y - stage->camera_y;
	} else {
		anchor->x = stage->camera_x + item->rel_x;
		anchor->y = stage->camera_y + item->rel_y;
		for (int k = item->index * 8 + 1; k <= item->index * 8 + 7; ++k) {
			stage->random_pairs[k][0] = env->random_int();
			stage->random_pairs[k][1] = env->random_int();
		}
	}

	item->x = item->rel_x + stage->camera_x;
	item->y = item->rel_y + stage->camera_y;
	item->last_mode = mode;
}
