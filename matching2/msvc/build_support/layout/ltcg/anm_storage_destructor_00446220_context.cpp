#define TH10_GAME_THREAD_SLOT_EXPORTED_ABI
#pragma code_seg(".text$00dslot")
#include "th10/game/game_thread.hpp"
#pragma code_seg()
#include "../../../src/core/sprtlib/anm_storage_destructor.cpp"
#pragma code_seg(".text$02context")
extern "C" void __stdcall DestroyAnmStorageContext(AnimationManagerStorage* state) { state->~AnimationManagerStorage(); }
#pragma code_seg()
