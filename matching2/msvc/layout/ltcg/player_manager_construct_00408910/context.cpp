// Compiler context only; never selected as recovered game code. The caller
// constructs in place so that it needs no cleanup state of its own.
#include "../../../src/game/player_manager_construct_00408910.cpp"

inline void* __cdecl operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$05context")
PlayerManager_00408910* __stdcall PlayerManagerConstructCompilerContext(void* block) {
    return new (block) PlayerManager_00408910;
}
#pragma code_seg()
