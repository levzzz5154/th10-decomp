// =============================================================================
// param_block_interp.hpp - Four-block parameter interpolator (0x004049A0)
// =============================================================================
#ifndef TH10_MATH_PARAM_BLOCK_INTERP_HPP
#define TH10_MATH_PARAM_BLOCK_INTERP_HPP

#include "th10/math/quantized_vector.hpp"

enum {
    PARAM_BLOCK_INTERP_SENTINEL = -999999,
    // Mode 7 integrates block B into block A every frame; mode 17 adds a
    // second order, integrating B into D and D into A. Mode 8 evaluates a
    // cubic Hermite spline across all four blocks. Every other mode is an
    // eased blend from A toward B through the shared easing table.
    PARAM_BLOCK_INTERP_MODE_INTEGRATE = 7,
    PARAM_BLOCK_INTERP_MODE_INTEGRATE2 = 17,
    PARAM_BLOCK_INTERP_MODE_HERMITE = 8
};

// Retail layout, 0x8C bytes. The four parameter blocks are the spline's value,
// target, start tangent and end tangent respectively.
struct ParamBlockInterp {
    QuantizedVector blocks[4];  // +0x00, +0x1C, +0x38, +0x54
    int previous;               // +0x70
    int current;                // +0x74
    float elapsed;             // +0x78
    const float* speed;        // +0x7C, points at the shared time scale
    int flags;                 // +0x80, bit 0 records sentinel initialization
    int duration;              // +0x84, cleared when the run completes
    int mode;                  // +0x88
};

// Advance the interpolator one frame and publish the resulting block through
// `result`, which is also the return value.
QuantizedVector* ParamBlockInterp_Tick(ParamBlockInterp* state,
                                       QuantizedVector* result);

#endif // TH10_MATH_PARAM_BLOCK_INTERP_HPP
