// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/bullet_entity_release_resource.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityReleaseResourceCompilerContext(
        BulletEntity6** entities, int count) {
    int released = 0;
    for (int index = 0; index < count; ++index) {
        entities[index]->ReleaseResource();
        ++released;
    }
    return released;
}
#pragma code_seg()
