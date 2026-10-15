#include "th10/math/interpolator_step.hpp"
#include "th10/math/vector.hpp"

// 0x00404610: Interpolator<Vec3>::Step. The interpolator arrives in EAX and
// the result is written through EDI.
template struct Interpolator<Vec3>;

// Template members take the section in effect at the end of the file.
#pragma code_seg(".text$00404610_fn")
