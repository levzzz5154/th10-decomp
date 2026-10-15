#pragma once
// The stage's animation file reload, run on a worker thread.
#include "th10/game/stage_anm_reload.hpp"

// 0x0040B4F0: reload the owner's stage. Retail keeps this copy without a
// remaining caller; the owner arrives in EAX.
#pragma code_seg(".text$01owner")
