// Compiler context only: a stand-in for the common laser constructor. It
// forwards to an opaque body, so the pass keeps the laser in EDX, drops the
// unused first argument at the call sites and assumes nothing about which
// registers survive the call.
#include "th10/game/laser_spawn.hpp"

extern "C" LaserBase* __fastcall LaserBaseConstructBody(void* unused, LaserBase* self);

#pragma code_seg(".text$0041c030_fn")
__declspec(noinline) LaserBase* __fastcall
LaserBase_Construct2(void*, LaserBase* self) {
    return LaserBaseConstructBody(0, self);
}
#pragma code_seg()
