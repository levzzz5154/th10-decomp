// Compiler context only; never selected as recovered game code.
#include "../../src/game/player_delete.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_00425090(Player** objects, int count) {
    for (int index = 0; index < count; ++index) Player_Delete(objects[index]);
}
#pragma code_seg()
