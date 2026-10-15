// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/bullet_entity_find_by_id_0040cf90.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityFindByIdCompilerContext(
    BulletEntityFindByIdManager_0040cf90** managers, int count, int id) {
    int matches = 0;
    while (count--) {
        if ((*managers++)->FindById(id) != 0)
            ++matches;
    }
    return matches;
}
#pragma code_seg()
