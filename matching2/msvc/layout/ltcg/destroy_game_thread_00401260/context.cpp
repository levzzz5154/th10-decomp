// Compiler context only; never selected as recovered game code.
// The slot destructor's out-of-line copy (0x00401FF0) is emitted here.
// Keep ECX as the slot destructor receiver for the two unwind tail calls.
// Without a public ABI root, LTCG privately changes the receiver to ESI.
#define TH10_GAME_THREAD_SLOT_EXPORTED_ABI
#pragma code_seg(".text$04slot")
#include "th10/game/game_thread.hpp"
#pragma code_seg()
#include "../../../src/game/ascii/destructor.cpp"
#pragma code_seg(".text$02context")
extern "C" void __stdcall DestroyGameThreadContext_00401260(GameThread* thread) { thread->~GameThread(); }
#pragma code_seg()
