// Compiler context only; never selected as recovered game code. The verbatim
// grid-scanner source compiles inside this TU so the /GL pass sees the same
// IL shape that produced the retail pattern-in-EAX promotion, with the real
// cell spawner (0x004067D0) as its callee.
#include "th10/game/enemy_grid_scan_004073e0.hpp"
#include "../../../src/game/bullet/enemy_grid_scan.cpp"
#include "../../../src/game/bullet/enemy_projectile_spawn.cpp"
#include "queue_pan.cpp"
