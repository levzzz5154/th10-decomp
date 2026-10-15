// Compiler context only: models of the callees, so the pass derives their
// register arguments. None of these bytes are selected.
#include "th10/game/enemy_grid_scan_004073e0.hpp"
extern "C" const float flt_5_2083335;
#include "enemy_grid_scan_dependencies/sound_pan.cpp"

extern "C" int __cdecl EnemyGridScanLeaf(void* pointer, int value);

// Stand-in for 0x004067D0 (still assembly). It keeps the pattern live across
// calls beside a record pointer and two counters, which puts it in EBX as in
// retail; taking the manager's address keeps the manager on the stack.
#pragma code_seg(".text$004067d0_fn")
__declspec(noinline) int __stdcall SpawnPatternCell_004067d0(
        ProjectilePattern_004073e0* pattern, ProjectileManager_004073e0* manager,
        int column, int row, float aim) {
    EnemyGridScanLeaf(&manager, 0);
    ProjectileRecord_004073e0* record = manager->current;
    int tries = 0;
    int zero = 0;
    for (;;) {
        if (record->active == zero)
            break;
        ++record;
        if (record->active == 5)
            record = manager->records;
        if (++tries >= 2000)
            return 1;
    }
    manager->current = record;
    record->active = (short)(pattern->layout + column + row + EnemyGridScanLeaf(record, (int)aim) +
                             pattern->columns + EnemyGridScanLeaf(pattern, tries));
    return 0;
}
#pragma code_seg()
