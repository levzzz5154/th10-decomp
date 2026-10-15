// Compiler context only; never selected as recovered game code.
#include "th10/game/enemy_grid_scan_004073e0.hpp"
#include "../../../src/game/bullet/enemy_grid_scan.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall EnemyGridScanContext(
        ProjectilePattern_004073e0* patterns, ProjectileManager_004073e0* manager, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += EnemyGrid_ScanCells_004073e0(&patterns[index], manager);
    return total;
}
#pragma code_seg()
#pragma inline_depth()
