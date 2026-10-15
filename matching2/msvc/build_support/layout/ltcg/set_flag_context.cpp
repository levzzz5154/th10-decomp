// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00401cb0_00401cb0.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetPrimaryColorAlphaCompilerContext(Entity** entities, int count, char alpha) {
    Entity** cursor = entities;
    while (count--) {
        Entity* entity = *cursor++;
        entity->SetPrimaryColorAlpha(alpha);
        entity->SetPrimaryColorAlpha(alpha);
    }
    return 0;
}
#pragma code_seg()
