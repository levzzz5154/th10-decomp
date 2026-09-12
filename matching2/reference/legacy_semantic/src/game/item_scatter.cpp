#include "th10/game/item_scatter.hpp"

#include <cmath>

namespace {

const float kPi = 3.1415927f;
const float kTwoPi = 6.2831855f;
const float kHalfPi = 1.5707964f;
const float kQuarterPi = 0.78539819f;
const float kSpawnAngle = -1.5707964f;
const float kSpawnSpeed = 2.2f;
const int kDropGroupCount = 11;

float NormalizeAngle(float angle) {
    while (angle > kPi) {
        angle -= kTwoPi;
    }
    while (angle < -kPi) {
        angle += kTwoPi;
    }
    return angle;
}

}  // namespace

// 0x0040C9D0 - Scatter each configured item group around the plan origin,
// consume all group counts, and return the number of items emitted.
int ItemDrop_ScatterGroups(ItemDropPlan* plan,
                           const ItemDropEnv* env) {
    float angle = env->random_unit() * kPi;
    int spawned = 0;

    for (int group = 0; group < kDropGroupCount; ++group) {
        for (int item = 0; item < plan->counts[group]; ++item) {
            const float radius = env->random_unit();
            ItemDropVec3 position = {
                plan->origin.x + std::cos(angle) * plan->radius_x * radius,
                plan->origin.y + std::sin(angle) * plan->radius_y * radius,
                plan->origin.z
            };

            env->spawn(position, group + 1, -1, kSpawnAngle, kSpawnSpeed);
            ++spawned;

            angle += kHalfPi + env->random_signed() * kQuarterPi;
            angle = NormalizeAngle(angle);
        }
    }

    for (int group = 0; group < 12; ++group) {
        plan->counts[group] = 0;
    }
    return spawned;
}
