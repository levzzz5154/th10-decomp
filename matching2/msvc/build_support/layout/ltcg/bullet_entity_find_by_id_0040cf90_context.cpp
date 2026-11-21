// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/enemy_find_by_id.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityFindByIdCompilerContext(
    EnemyListFinder** managers, int count, int id) {
    int matches = 0;
    while (count--) {
        if ((*managers++)->FindById(id) != 0)
            ++matches;
    }
    return matches;
}
#pragma code_seg()
