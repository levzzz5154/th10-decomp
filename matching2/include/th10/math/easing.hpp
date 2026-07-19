#pragma once

// Piecewise easing selector used by animation interpolation. The mode is a
// hidden retail register argument; the conventional form makes it explicit.
float Easing_Evaluate(int mode, float numerator, float denominator);
