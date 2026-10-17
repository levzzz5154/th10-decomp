// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/enemy_data_start.cpp"

#pragma code_seg(".text$0040dc00_ctx")
extern "C" int __stdcall RigEntry(EnemyTick** enemies, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) total += EnemyDataStart(enemies[i]);
    return total;
}
#pragma code_seg()
