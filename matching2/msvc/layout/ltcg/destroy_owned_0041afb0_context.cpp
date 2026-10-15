// Compiler context only; never selected as recovered game code.
#include "../../src/game/item/item_manager_delete.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_0041afb0(ItemManager** objects, int count) {
    for (int index = 0; index < count; ++index) ItemManager_Delete(objects[index]);
}
#pragma code_seg()
