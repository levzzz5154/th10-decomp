// Compiler context only; never selected as recovered game code. The caller
// constructs in place so that it needs no cleanup state of its own.
#include "../../../src/game/card/card_construct.cpp"

inline void* __cdecl operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$05context")
Card* __stdcall CardConstructCompilerContext(void* block) {
    return new (block) Card;
}
#pragma code_seg()
