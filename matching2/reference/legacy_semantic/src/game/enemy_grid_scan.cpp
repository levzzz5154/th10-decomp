#include "th10/game/enemy_grid_scan.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// 0x004073E0 - Scan every cell of the enemy's shot grid, aiming each cell at
// the player. The aim angle is atan2 of the player offset, or a quarter turn
// when the player sits exactly on the emitter. A non-zero visitor result
// aborts the scan; flag 0x200 additionally records a timing event.
int EnemyGrid_ScanCells(float player_x, float player_y, float origin_x,
                        float origin_y, int column_count, int row_count,
                        Word flags,
                        float (*arc_tangent)(float delta_y, float delta_x),
                        EnemyCellVisitor visit, void* context,
                        void (*record_event)(void)) {
	float delta_x = player_x - origin_x;
	float delta_y = player_y - origin_y;
	float aim_angle;
	if (delta_x == 0.0f && delta_y == 0.0f) {
		aim_angle = 1.5707964f;
	} else {
		aim_angle = arc_tangent(delta_y, delta_x);
	}
	for (int row = 0; row < row_count; ++row) {
		int aborted = 0;
		for (int column = 0; column < column_count; ++column) {
			if (visit(column, row, aim_angle, context) != 0) {
				aborted = 1;
				break;
			}
		}
		if (aborted) break;
	}
	if ((flags & 0x200u) != 0) record_event();
	return 0;
}
