// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/bullet_entity_clear_resource_list_0040c6e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityClearResourceListCompilerContext(
        BulletEntity_0040c6e0** entities, int count) {
    while (count--)
        (*entities++)->ClearResourceList();
    return 0;
}
#pragma code_seg()
