#include "th10/math/interpolator_step.hpp"

// 0x00441950: Interpolator<int>::Step. The interpolator arrives in ESI.
template struct Interpolator<int>;

// Template members take the section in effect at the end of the file.
#pragma code_seg(".text$00441950_fn")
