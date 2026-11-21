// Compiler context only; never selected as recovered game code.
#include "th10/game/bullet_spawn_pattern.hpp"
#include "../../../src/game/bullet/bullet_spawn_pattern.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall EnemyGridScanContext(
        ProjectilePattern* patterns, ProjectileManager2* manager, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += BulletManager_SpawnPattern(&patterns[index], manager);
    return total;
}
#pragma code_seg()
#pragma inline_depth()
