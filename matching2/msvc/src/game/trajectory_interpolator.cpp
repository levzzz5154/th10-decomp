#include "th10/math/trajectory_vector.hpp"
#include "th10/math/interpolator_step.hpp"

// 0x00412AC0: bullet trajectory interpolation. The receiver arrives in ESI,
// and the returned vector is written through EDI.
template struct Interpolator<TrajectoryVec2>;

#pragma code_seg(".text$00412ac0_fn")
