// Compiler context only; this translation unit is never selected as recovered
// game code. It supplies the 0x004067D0 model's caller, the grid scanner
// 0x004073E0, the panned sound queue 0x0043DD10 it calls, and the link entry
// that reaches the selected body.
#include "th10/game/enemy_grid_scan.hpp"

extern "C" const float flt_5_2083335;

#define code_seg(name) code_seg(".text$0043dd10_fn")
#include "../../../build_support/layout/ltcg/enemy_grid_scan_dependencies/sound_pan.cpp"
#undef code_seg

#include "../../../src/game/bullet/enemy_grid_scan.cpp"


// The entry only anchors the link; its body is never exported as recovered
// code. The scanner stays a real call so the spawner's register convention is
// derived exactly as in the equivalence model.
#pragma inline_depth(0)
#pragma code_seg(".text$zz_entry")
extern "C" int __stdcall ProjectileSpawnCellContext(
        ProjectilePattern* patterns, ProjectileManager2* manager, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += EnemyGrid_ScanCells2(&patterns[index], manager);
    return total;
}
#pragma code_seg()
#pragma inline_depth()
