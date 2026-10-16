// Context for the 0x004067D0 recovery: its caller, the grid scanner
// 0x004073E0, with the panned sound queue it calls, so the /GL pass derives
// the cell spawner's retail convention (blueprint in EBX, the rest on the
// stack). The sections are moved past the spawner's jump tables, so the gate
// sees the calls as leaving the function.
#include "th10/game/enemy_grid_scan.hpp"
extern "C" const float flt_5_2083335;
#define code_seg(name) code_seg(".text$zz_004073e0")
#include "../../../../layout/ltcg/enemy_grid_scan_dependencies/sound_pan.cpp"
#include "../../../../../src/game/bullet/enemy_grid_scan.cpp"
#undef code_seg

// The link entry: a plain caller of the scanner.
#pragma inline_depth(0)
#pragma code_seg(".text$zz_004073e0_entry")
extern "C" int __stdcall ProjectileSpawnCellContext(
        ProjectilePattern* patterns, ProjectileManager2* manager, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += EnemyGrid_ScanCells2(&patterns[index], manager);
    return total;
}
#pragma code_seg()
#pragma inline_depth()
