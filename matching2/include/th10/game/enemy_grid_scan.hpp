#pragma once

// Enemy shot-grid cell scan with per-cell aim (retail 0x004073E0).
#include "th10/util/scalars.hpp"

// --- 0x004073E0 --------------------------------------------------------------
typedef int (*EnemyCellVisitor)(int column, int row, float aim_angle,
                                 void* context);

int EnemyGrid_ScanCells(float player_x, float player_y, float origin_x,
                        float origin_y, int column_count, int row_count,
                        Word flags,
                        float (*arc_tangent)(float delta_y, float delta_x),
                        EnemyCellVisitor visit, void* context,
                        void (*record_event)(void));
