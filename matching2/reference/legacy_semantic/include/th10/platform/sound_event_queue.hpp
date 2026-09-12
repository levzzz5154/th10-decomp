#pragma once

// Sound event queueing into per-slot id/count arrays (retail 0x0043DD10).

// --- 0x0043DD10 --------------------------------------------------------------
void SoundQueue_QueueEvent(int* slot_ids, int* slot_counts,
                           int (*slot_stamps)[128], int* volume_table,
                           int sound_id, short priority, int stamp);
