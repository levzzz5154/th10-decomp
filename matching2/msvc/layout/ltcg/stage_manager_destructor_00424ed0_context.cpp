#define TH10_PLAYER_SPRITE_EXPORTED_ABI
#pragma code_seg(".text$00bslot")
#include "th10/game/player.hpp"
#pragma code_seg()
#include "../../src/game/player/player_destructor.cpp"
#pragma code_seg(".text$02context")
extern "C" void __stdcall StageManagerDestroyContext(Player* player) { player->~Player(); }
#pragma code_seg()
