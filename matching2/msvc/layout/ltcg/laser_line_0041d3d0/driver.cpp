// Complete public laser callback and actual existing link-entry wrapper.
#include "../../../src/game/laser/laser_line.cpp"
struct Game;
extern "C" int __stdcall Game_Update(Game* context);
#pragma code_seg(".text$00entry")
void __fastcall Game_UpdateCompilerCaller_004187c0(void* context) {
    Game_Update(reinterpret_cast<Game*>(context));
}
#pragma code_seg()
