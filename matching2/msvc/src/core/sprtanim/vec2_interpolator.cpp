#include "th10/math/interpolator_step.hpp"
#include "th10/math/vector.hpp"

// 0x00441AD0: Interpolator<Vec2>::Step. The interpolator arrives in ESI and
// the result is written through EDI.
template struct Interpolator<Vec2>;

// Template members take the section in effect at the end of the file.
#pragma code_seg(".text$00441ad0_fn")
