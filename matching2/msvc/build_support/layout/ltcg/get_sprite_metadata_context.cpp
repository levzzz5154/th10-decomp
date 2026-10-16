#include "../../../src/unreferenced/FUN.cpp_401cd0.cpp"

#pragma code_seg(".text$03context")
int __stdcall GetSpriteMetadataCompilerContext(Entity** entities, int count) {
    int total = 0;
    Entity** cursor = entities;
    while (count--) {
        Entity* entity = *cursor++;
        total += (int)entity->GetSpriteMetadata();
        total += (int)entity->GetSpriteMetadata();
    }
    return total;
}
#pragma code_seg()
