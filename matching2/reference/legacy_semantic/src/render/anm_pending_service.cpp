#include "th10/render/anm_pending_service.hpp"
#include "th10/game/player_motion.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// 0x00447700 - Service the ANM archive's pending-entry table (0x21 slots in
// retail). An entry with a script but no pending flag resumes the cursor
// advance and the sweep stops there (0 on success, -1 on failure). Entries
// flagged pending are discarded, freed, and their slot cleared.
int AnmArchive_ServicePending(void* context, AnmPendingEntry** slots,
                              int slot_count,
                              int (*advance)(void* context,
                                             AnmPendingEntry* entry),
                              void (*discard)(AnmPendingEntry* entry),
                              void (*free_memory)(void* memory)) {
	for (int index = 0; index < slot_count; ++index) {
		AnmPendingEntry* entry = slots[index];
		if (entry == 0) continue;
		if (entry->pending == 0) {
			if (entry->script != 0) {
				return advance(context, entry) != 0 ? 0 : -1;
			}
		} else {
			discard(entry);
			free_memory(entry);
			slots[index] = 0;
		}
	}
	return 0;
}
