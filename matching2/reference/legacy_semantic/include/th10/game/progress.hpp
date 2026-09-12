#pragma once

// Persistent game-progress block rooted at DAT_0047783c. The layout holds one
// 0x437C-byte table per shot type (character * 3 + shot, six total), with
// per-stage practice-availability bytes at 8-byte stride starting at +0x4E9,
// followed by sixteen shot-type record flags at +0x1D882 (indices 0..5 main,
// 6..11 extra variants, 12 the aggregate extra flag).
int  GameProgress_HasAnyPlayRecord(const void* progress);
void GameProgress_UnlockAllStages(void* progress);
