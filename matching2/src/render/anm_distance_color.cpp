#include "th10/render/anm_distance_color.hpp"

#include <cmath>
#include <cstring>

namespace {

unsigned char ClampByte(unsigned int value) {
    return static_cast<unsigned char>(value > 255 ? 255 : value);
}

uint32_t PackColor(const unsigned char color[4]) {
    uint32_t packed;
    std::memcpy(&packed, color, sizeof(packed));
    return packed;
}

} // namespace

int AnmDistanceColor_Apply(uint32_t input_color, const float position[3],
                           const float camera[3], int tint_enabled,
                           const unsigned char tint[4], float near_distance,
                           float far_distance, uint32_t far_color,
                           uint32_t* output_color) {
    if (output_color == nullptr || position == nullptr || camera == nullptr)
        return -1;
    unsigned char color[4];
    std::memcpy(color, &input_color, sizeof(color));
    if (tint_enabled != 0 && tint != nullptr) {
        for (int channel = 0; channel < 4; ++channel)
            color[channel] = ClampByte(
                static_cast<unsigned int>(color[channel]) * tint[channel] >> 7);
    }
    float delta[3];
    for (int axis = 0; axis < 3; ++axis)
        delta[axis] = position[axis] - camera[axis];
    const float distance = std::sqrt(
        delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
    if (distance <= near_distance) {
        *output_color = PackColor(color);
        return 0;
    }
    const float denominator = near_distance - far_distance;
    if (denominator == 0.0f)
        return -1;
    const float amount = (near_distance - distance) / denominator;
    if (amount >= 1.0f)
        return -1;
    unsigned char far[4];
    std::memcpy(far, &far_color, sizeof(far));
    for (int channel = 0; channel < 3; ++channel)
        color[channel] = static_cast<unsigned char>(
            static_cast<int>(color[channel]) -
            static_cast<int>((static_cast<int>(color[channel]) -
                              static_cast<int>(far[channel])) * amount));
    color[3] = static_cast<unsigned char>((1.0f - amount) * color[3]);
    *output_color = PackColor(color);
    return 0;
}

// Semantic reconstruction 0x00443FB0 - distance-colored ANM quad draw.
int AnmVm_DrawDistanceColored(const AnmVmState* vm,
                              const AnmDistanceColorEnv* env) {
    if (env->validate(env->context, vm) != 0)
        return -1;

    const unsigned char* source =
        (vm->flags & 0x8000u) != 0 ? vm->color2 : vm->color;
    uint32_t input_color;
    std::memcpy(&input_color, source, sizeof(input_color));
    float position[3];
    for (int axis = 0; axis < 3; ++axis)
        position[axis] = vm->position[axis] + vm->velocity[axis] +
                         vm->alt_position[axis];
    uint32_t packed;
    if (AnmDistanceColor_Apply(input_color, position, env->camera,
                               env->tint_enabled, env->tint,
                               env->near_distance, env->far_distance,
                               env->far_color, &packed) != 0)
        return -1;
    for (int vertex = 0; vertex < 4; ++vertex)
        env->output_colors[vertex] = packed;
    return env->draw(env->context, vm, 2);
}
