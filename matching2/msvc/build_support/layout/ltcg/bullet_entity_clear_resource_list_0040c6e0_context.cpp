// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/bullet_entity_clear_resource_list.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityClearResourceListCompilerContext(
        BulletEntity3** entities, int count) {
    while (count--)
        (*entities++)->ClearResourceList();
    return 0;
}
#pragma code_seg()
