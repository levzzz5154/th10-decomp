// Compiler context only: a stand-in for the common laser constructor. It
// forwards to an opaque body, so the pass keeps the laser in EDX, drops the
// unused first argument at the call sites and assumes nothing about which
// registers survive the call.
#include "th10/game/laser_spawn_0041c510.hpp"

extern "C" LaserBase_0041c030* __fastcall LaserBaseConstructBody(void* unused, LaserBase_0041c030* self);

#pragma code_seg(".text$0041c030_fn")
__declspec(noinline) LaserBase_0041c030* __fastcall
LaserBase_Construct_0041c030(void*, LaserBase_0041c030* self) {
    return LaserBaseConstructBody(0, self);
}
#pragma code_seg()
