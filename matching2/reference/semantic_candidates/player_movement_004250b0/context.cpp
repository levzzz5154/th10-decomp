#include "types.hpp"
extern "C" MovementState* movement_player;
#pragma code_seg(".text$0044bd00_context")
extern "C" int __stdcall MovementCompilerContext() { return PlayerMovement_004250b0(movement_player); }
