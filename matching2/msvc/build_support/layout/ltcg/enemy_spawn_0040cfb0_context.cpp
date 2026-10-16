// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/game/enemy/enemy_spawn.cpp"

extern "C" int __cdecl EnemySpawnEscape(void* pointer, int value);

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall EnemySpawnContext(EnemySpawn2** spawns, EnemyCtrlSpawnView** managers,
                                           const char** entries, int count) {
    // The run state is reachable through pointers in the real program.
    int total = EnemySpawnEscape(&g_globals, 0);
    for (int index = 0; index < count; ++index) {
        total += EnemySpawnEscape(spawns[index], index);
        total += EnemySpawnEscape(spawns[index]->Create(managers[index], entries[index]), total);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()

// A stand-in for the record initialiser 0x0040D830. It keeps the record
// across opaque calls the way the real body does, so the record is handed
// over in ESI.
#pragma code_seg(".text$0040d830_fn")
Enemy4::Enemy4(const char* entry) {
    EnemySpawnEscape(this, 0);
    EnemySpawnEscape((void*)entry, 1);
    EnemySpawnEscape(this, 2);
}
#pragma code_seg()
