// Compiler context only; never selected as recovered game code.
#include "../../../src/game/game/game_delete.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_00418150(Game** objects, int count) {
    for (int index = 0; index < count; ++index) Game_Delete(objects[index]);
}
#pragma code_seg()
