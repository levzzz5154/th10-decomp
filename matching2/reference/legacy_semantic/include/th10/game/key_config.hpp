#pragma once

// Key config slot reassignment (retail 0x00430250).

// --- 0x00430250 --------------------------------------------------------------
void KeyConfig_ReassignSlot(short* slots, int slot_index, short new_key,
                            void (*on_changed)(int slot_index),
                            void* sound_block,
                            void (*play_sound)(void* sound_block, int index));
