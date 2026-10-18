// Compiler context only; this translation unit is never selected as recovered
// game code. It is the second context input of the equivalent 0x00406D90 model
// (build_support/contexts/equivalent/game/context/
// projectile_command_scan_cells.cpp) without the merged section: the real grid
// scanner 0x004073E0 with the cell-spawner stand-in 0x004067D0 and the panned
// sound queue 0x0043DD10, each in its own retail section.
#include "enemy_grid_scan_anchors.cpp"
#include "../../../src/game/bullet/enemy_grid_scan.cpp"
