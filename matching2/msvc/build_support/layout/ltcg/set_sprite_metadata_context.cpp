#include "../../../src/unreferenced/FUN.cpp_401d10.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetSpriteMetadataCompilerContext(Entity** entities, int count, void* metadata) {
    Entity** cursor = entities;
    while (count--) {
        Entity* entity = *cursor++;
        entity->SetSpriteMetadata(metadata);
        entity->SetSpriteMetadata(metadata);
    }
    return 0;
}
#pragma code_seg()
