#pragma once

#include "th10/script/anm_vm_tick.hpp"

#include <cstdint>

struct AnmDistanceColorEnv {
    void* context;
    float camera[3];
    float near_distance;
    float far_distance;
    uint32_t far_color;
    int tint_enabled;
    unsigned char tint[4]; // b, g, r, a; 0x80 is unity
    uint32_t* output_colors; // four vertex-color slots
    int (*validate)(void* context, const AnmVmState* vm);
    int (*draw)(void* context, const AnmVmState* vm, int mode);
};

// 0x00443FB0 - select/tint the VM color, attenuate it by camera distance,
// publish it to the four quad vertices, and draw in mode 2.
int AnmVm_DrawDistanceColored(const AnmVmState* vm,
                              const AnmDistanceColorEnv* env);

// Apply the retail 0x00443FB0 channel math to a packed B,G,R,A color.
int AnmDistanceColor_Apply(uint32_t input_color, const float position[3],
                           const float camera[3], int tint_enabled,
                           const unsigned char tint[4], float near_distance,
                           float far_distance, uint32_t far_color,
                           uint32_t* output_color);
