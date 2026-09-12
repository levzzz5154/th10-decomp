#include "th10/render/anm_script_table_sweep.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>

namespace {


} // namespace

// 0x00403990 - walks the manager's record table and, for every record whose
// active bit is set, runs the ANM interpreter on each sprite slot in its
// packed slot list. A slot is live when its VM still has an instruction
// cursor after the run; when no slot in the record survives (or the list is
// empty), the record's active bit is cleared. Returns 0 like retail.
int AnmScriptTable_Sweep(AnmSweepEnv* env) {
	for (int index = 0; index < *env->count; ++index) {
		AnmSweepRecord* record = env->records[index];
		if ((record->flags & 1u) == 0) {
			continue;
		}
		const AnmSpriteSlot* slot = record->slots;
		int live = 0;
		if (slot->id >= 0) {
			do {
				if (env->run_script(env->vm_pool, slot->vm_index) != 0) {
					live += 1;
				}
				slot = (const AnmSpriteSlot*)((const char*)slot + slot->step);
			} while (slot->id >= 0);
			if (live != 0) {
				continue;
			}
		}
		record->flags = (Byte)(record->flags & 0xFEu);
	}
	return 0;
}
