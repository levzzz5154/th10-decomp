#include "th10/render/anm_distance_color.hpp"

#include <cmath>
#include <cstring>

namespace {

unsigned char ClampByte(unsigned int value) {
    return static_cast<unsigned char>(value > 255 ? 255 : value);
}

} // namespace

// Semantic reconstruction 0x00443FB0 - distance-colored ANM quad draw.
int AnmVm_DrawDistanceColored(const AnmVmState* vm,
                              const AnmDistanceColorEnv* env) {
    if (env->validate(env->context, vm) != 0)
        return -1;

    unsigned char color[4];
    const unsigned char* source =
        (vm->flags & 0x8000u) != 0 ? vm->color2 : vm->color;
    std::memcpy(color, source, sizeof(color));
    if (env->tint_enabled != 0)
        for (int channel = 0; channel < 4; ++channel)
            color[channel] = ClampByte(
                static_cast<unsigned int>(color[channel]) *
                env->tint[channel] >> 7);

    float delta[3];
    for (int axis = 0; axis < 3; ++axis)
        delta[axis] = vm->position[axis] + vm->velocity[axis] +
                      vm->alt_position[axis] - env->camera[axis];
    const float distance = std::sqrt(
        delta[0] * delta[0] + delta[1] * delta[1] +
        delta[2] * delta[2]);

    if (distance > env->near_distance) {
        const float denominator = env->near_distance - env->far_distance;
        if (denominator == 0.0f)
            return -1;
        const float amount =
            (env->near_distance - distance) / denominator;
        if (amount >= 1.0f)
            return -1;
        const unsigned char* far =
            reinterpret_cast<const unsigned char*>(&env->far_color);
        for (int channel = 0; channel < 3; ++channel)
            color[channel] = static_cast<unsigned char>(
                static_cast<int>(color[channel]) -
                static_cast<int>(
                    (static_cast<int>(color[channel]) -
                     static_cast<int>(far[channel])) * amount));
        color[3] = static_cast<unsigned char>(
            static_cast<int>((1.0f - amount) * color[3]));
    }

    uint32_t packed;
    std::memcpy(&packed, color, sizeof(packed));
    for (int vertex = 0; vertex < 4; ++vertex)
        env->output_colors[vertex] = packed;
    return env->draw(env->context, vm, 2);
}
