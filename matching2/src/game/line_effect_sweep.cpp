#include "th10/game/line_effect_sweep.hpp"

#include <cmath>

namespace {

const float kInitialStep = 6.0f;
const float kStepLength = 12.0f;
const float kScreenOffsetX = 224.0f;
const float kScreenOffsetY = 16.0f;
const float kItemHalfExtent = 32.0f;
const int kSparkBaseAnimation = 17;
const int kItemKind = 8;
const float kItemAngle = -1.5707964f;
const float kItemSpeed = 0.6f;

bool IsItemSpawnVisible(const float position[3]) {
    return position[0] + kItemHalfExtent > -192.0f &&
           position[0] - kItemHalfExtent < 192.0f &&
           position[1] + kItemHalfExtent > 0.0f &&
           position[1] - kItemHalfExtent < 448.0f;
}

}  // namespace

// 0x0041E260 - Walk the line in twelve-unit intervals, spawning one sparkle
// per sample and optional cancellation items for samples inside the field.
int LineEffect_SweepIntoItems(LineEffect* line, int spawn_items,
                              const LineEffectSweepEnv* env) {
    if (line->length <= kStepLength) {
        line->finished = 1;
        return 0;
    }

    const float dx = std::cos(line->angle) * kInitialStep;
    const float dy = std::sin(line->angle) * kInitialStep;
    float position[3] = {
        line->origin[0] + dx,
        line->origin[1] + dy,
        line->origin[2]
    };
    float distance = kInitialStep;
    int spark_count = 0;

    do {
        float screen_position[3] = {
            position[0] + kScreenOffsetX,
            position[1] + kScreenOffsetY,
            position[2]
        };
        env->spawn_spark(
            screen_position,
            2 * line->animation_variant + kSparkBaseAnimation);
        ++spark_count;

        if (spawn_items && IsItemSpawnVisible(position)) {
            env->spawn_item(position, kItemKind, -1,
                            kItemAngle, kItemSpeed);
        }

        position[0] += 2.0f * dx;
        position[1] += 2.0f * dy;
        distance += kStepLength;
    } while (distance + kInitialStep < line->length);

    line->finished = 1;
    return spark_count;
}
