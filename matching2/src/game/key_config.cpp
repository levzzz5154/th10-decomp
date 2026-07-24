#include "th10/game/key_config.hpp"
#include "th10/game/player_motion.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// 0x00430250 - Rebind one of the five key-config slots. If another slot
// already holds the requested key it inherits this slot's old key (a swap),
// so no two slots ever share a binding; the change callback and the menu
// confirmation sound only fire when the binding actually changed.
void KeyConfig_ReassignSlot(short* slots, int slot_index, short new_key,
                            void (*on_changed)(int slot_index),
                            void* sound_block,
                            void (*play_sound)(void* sound_block, int index)) {
	short old_key = slots[slot_index];
	if (old_key == new_key) return;
	for (int index = 0; index < 5; ++index) {
		if (index != slot_index && slots[index] == new_key) {
			slots[index] = old_key;
		}
	}
	slots[slot_index] = new_key;
	on_changed(slot_index);
	play_sound(sound_block, 0);
}
