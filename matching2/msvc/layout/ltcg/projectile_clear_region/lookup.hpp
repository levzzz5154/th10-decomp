#pragma once
// The animation lookup at 0x004491C0 as this caller sees it: the id travels
// as the record the creation call returns.
#include "th10/render/animation_public_callers.hpp"
#include "../laser_cut/animation_ids.hpp"
struct AnimationLookup {
    __declspec(noinline) Entity* __fastcall Find(AnimationLookupContext* context, CutAnimationId id);
};
