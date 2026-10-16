// Complete Game_Update callback and its existing fastcall wrapper.
#include "../../../../src/game/game/game_update.cpp"
#pragma code_seg(".text$004187c0_context")
void __fastcall Game_UpdateCompilerCaller_004187c0(void* context) {
    Game_Update(reinterpret_cast<Game*>(context));
}
#pragma code_seg()
