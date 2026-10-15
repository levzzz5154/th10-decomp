// Existing public laser callback plus a complete actual fastcall wrapper.
// The 4187C0 wrapper is only the native link entry and earns no new credit.
#include "../../../../src/game/laser/laser_grow_update.cpp"
struct Game;
extern "C" int __stdcall Game_Update(Game* context);
#pragma code_seg(".text$10entry")
void __fastcall Game_UpdateCompilerCaller_004187c0(void* context) {
    Game_Update(reinterpret_cast<Game*>(context));
}
#pragma code_seg()
