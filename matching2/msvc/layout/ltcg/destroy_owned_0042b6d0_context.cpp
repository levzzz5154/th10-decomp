// Compiler context only; never selected as recovered game code.
#include "../../src/game/smollscore/effect_manager_delete.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_0042b6d0(EffectManager** objects, int count) {
    for (int index = 0; index < count; ++index) EffectManager_Delete(objects[index]);
}
#pragma code_seg()
