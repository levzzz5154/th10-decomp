#include "../../src/unidentified/FUN_00401cc0_00401cc0.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetPrimaryColorCompilerContext(Entity** entities, int count, uint32_t color) {
    Entity** cursor = entities;
    while (count--) {
        Entity* entity = *cursor++;
        entity->SetPrimaryColor(color);
        entity->SetPrimaryColor(color);
    }
    return 0;
}
#pragma code_seg()
