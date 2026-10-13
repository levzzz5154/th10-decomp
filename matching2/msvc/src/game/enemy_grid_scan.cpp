// 0x004073E0..0x004074A1: spawn a whole projectile pattern.
//
// The aim is the angle from the pattern's origin to the player (straight down
// when the two coincide). Every cell of the columns-by-rows grid is spawned
// with it, row by row, until the projectile pool is full; then the pattern's
// sound, if it has one, is queued panned to the origin. Always returns 0.
//
// The pattern arrives in EAX and the manager on the stack (RET 4); the cell
// spawner takes the pattern in EBX. Both conventions come from the native
// LTCG cluster layout/ltcg/enemy_grid_scan_004073e0.json.
#include "th10/game/enemy_grid_scan_004073e0.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" double __cdecl atan2(double, double);
#pragma intrinsic(atan2)

#pragma code_seg(".text$004073e0_fn")
int __stdcall EnemyGrid_ScanCells_004073e0(ProjectilePattern_004073e0* pattern,
                                           ProjectileManager_004073e0* manager) {
    float dx = data_00477834->x - pattern->x;
    float dy = data_00477834->y - pattern->y;
    float aim;
    if (dy == 0.0f && dx == 0.0f)
        aim = 1.5707964f;
    else
        aim = (float)atan2(dy, dx);
    for (int row = 0; row < pattern->rows; ++row) {
        for (int column = 0; column < pattern->columns; ++column) {
            if (SpawnPatternCell_004067d0(pattern, manager, column, row, aim) != 0)
                goto full;
        }
    }
full:
    if (pattern->flags & 0x200)
        data_00492590.QueuePan(pattern->sound, pattern->x);
    return 0;
}
#pragma code_seg()

// Whole-program context: the panned sound queue anchor whose body the /GL
// pass needs to derive the retail register state at the call above. None of
// these bytes are exported as recovered code.

