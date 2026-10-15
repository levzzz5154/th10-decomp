// Compiler context only; never selected as recovered game code.
#include "../../src/game/smollscore/smoll_score_delete.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_0042b6d0(SmollScore** objects, int count) {
    for (int index = 0; index < count; ++index) SmollScore_Delete(objects[index]);
}
#pragma code_seg()
