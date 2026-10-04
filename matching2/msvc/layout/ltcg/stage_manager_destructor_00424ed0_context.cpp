#define TH10_GAME_THREAD_SLOT_EXPORTED_ABI
#pragma code_seg(".text$00bslot")
#include "th10/game/game_thread.hpp"
#pragma code_seg()
#include "../../src/game/stage_manager_destructor_00424ed0.cpp"
#pragma code_seg(".text$02context")
extern "C" void __stdcall StageManagerDestroyContext(StageManager_00424ed0* stage) { stage->~StageManager_00424ed0(); }
#pragma code_seg()
