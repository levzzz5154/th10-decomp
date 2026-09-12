#include "th10/game/laser_segment_cut.hpp"

#include <cmath>
#include <vector>

namespace {

const float kHalfStep = 6.0f;
const float kStep = 12.0f;
const float kItemRadius = 32.0f;

bool InsideCircle(const float p[3], const float center[3], float radius) {
    const float dx = center[0] - p[0];
    const float dy = center[1] - p[1];
    return dx * dx + dy * dy <= radius * radius;
}

bool InsideRectangle(const float p[3], const LaserCutRegion& region) {
    const float hx = region.size[0] * 0.5f;
    const float hy = region.size[1] * 0.5f;
    return p[0] >= region.center[0] - hx &&
           p[0] <= region.center[0] + hx &&
           p[1] >= region.center[1] - hy &&
           p[1] <= region.center[1] + hy;
}

bool ItemVisible(const float p[3]) {
    return p[0] + kItemRadius > -192.0f &&
           p[0] - kItemRadius < 192.0f &&
           p[1] + kItemRadius > 0.0f &&
           p[1] - kItemRadius < 448.0f;
}

void PreserveUncutRuns(LaserCutState* laser, const std::vector<uint8_t>& cut,
                       float step_x, float step_y, const LaserCutOps* ops) {
    const int count = static_cast<int>(cut.size());
    int cursor = 0;
    while (cursor < count && cut[cursor] != 0) ++cursor;

    if (cursor != 0) {
        laser->length = 0.0f;
    } else {
        while (cursor < count && cut[cursor] == 0) ++cursor;
        if (cursor == count) return;
        laser->length = static_cast<float>(cursor) * kStep;
    }

    while (cursor < count) {
        while (cursor < count && cut[cursor] != 0) ++cursor;
        if (cursor >= count) break;
        const int start = cursor;
        while (cursor < count && cut[cursor] == 0) ++cursor;
        const int run = cursor - start;

        LaserCutState segment = *laser;
        segment.origin[0] += step_x * static_cast<float>(start);
        segment.origin[1] += step_y * static_cast<float>(start);
        segment.length = static_cast<float>(run) * kStep;
        segment.width = segment.length;
        segment.distance_budget -= static_cast<float>(start) * kStep;
        ops->clone_segment(ops->context, &segment);
    }
}

template <typename Predicate, typename Effect>
int CutSamples(LaserCutState* laser, int spawn_items,
               const LaserCutOps* ops, Predicate inside, Effect effect) {
    if (laser->length <= kStep) return 0;

    const float half_x = std::cos(laser->angle) * kHalfStep;
    const float half_y = std::sin(laser->angle) * kHalfStep;
    const float step_x = half_x * 2.0f;
    const float step_y = half_y * 2.0f;
    float position[3] = {
        laser->origin[0] + half_x,
        laser->origin[1] + half_y,
        laser->origin[2]
    };
    float distance = kHalfStep;
    std::vector<uint8_t> cut;
    int hit_count = 0;

    do {
        const bool hit = inside(position);
        cut.push_back(hit ? 1u : 0u);
        if (hit) {
            ++hit_count;
            effect(position);
            if (spawn_items != 0 && ItemVisible(position))
                ops->spawn_item(ops->context, position, 8, -1,
                                -1.5707964f, 0.6f);
        }
        position[0] += step_x;
        position[1] += step_y;
        distance += kStep;
    } while (distance + kHalfStep < laser->length);

    if (hit_count != 0)
        PreserveUncutRuns(laser, cut, step_x, step_y, ops);
    return hit_count;
}

void PreserveTrimmedRuns(LaserCutState* laser,
                         const std::vector<uint8_t>& cut,
                         float step_x, float step_y,
                         const LaserCutOps* ops) {
    const int count = static_cast<int>(cut.size());
    int cursor = 0;
    while (cursor < count && cut[cursor] != 0) ++cursor;
    if (cursor == count) {
        laser->retired = true;
        return;
    }
    if (cursor != 0) {
        const float removed = static_cast<float>(cursor) * kStep;
        laser->origin[0] += step_x * static_cast<float>(cursor);
        laser->origin[1] += step_y * static_cast<float>(cursor);
        laser->length -= removed;
        if (laser->length <= 18.0f) {
            laser->retired = true;
            return;
        }
        laser->length_limit = laser->length;
        laser->traveled = removed;
    }
    const int first_uncut = cursor;
    while (cursor < count && cut[cursor] == 0) ++cursor;
    if (cursor == count) return;
    const float first_length =
        static_cast<float>(cursor - first_uncut) * kStep;
    laser->length_limit -= laser->length - first_length;
    laser->length = first_length;
    if (first_length < 18.0f) laser->retired = true;
    while (cursor < count) {
        while (cursor < count && cut[cursor] != 0) ++cursor;
        if (cursor >= count) break;
        const int start = cursor;
        while (cursor < count && cut[cursor] == 0) ++cursor;
        const float run_length = static_cast<float>(cursor - start) * kStep;
        if (run_length <= 18.0f) continue;
        LaserCutState segment = *laser;
        segment.retired = false;
        segment.origin[0] = laser->origin[0] +
                            step_x * static_cast<float>(start - first_uncut);
        segment.origin[1] = laser->origin[1] +
                            step_y * static_cast<float>(start - first_uncut);
        segment.length = run_length;
        segment.width = run_length;
        ops->clone_segment(ops->context, &segment);
    }
}

template <typename Predicate, typename Effect>
int TrimSamples(LaserCutState* laser, int spawn_items,
                const LaserCutOps* ops, Predicate inside, Effect effect) {
    if (laser->length < kStep) return 0;
    const float half_x = std::cos(laser->angle) * kHalfStep;
    const float half_y = std::sin(laser->angle) * kHalfStep;
    const float step_x = half_x * 2.0f;
    const float step_y = half_y * 2.0f;
    float position[3] = {laser->origin[0] + half_x,
                         laser->origin[1] + half_y, laser->origin[2]};
    float distance = kHalfStep;
    std::vector<uint8_t> cut;
    int hits = 0;
    do {
        const bool hit = inside(position);
        cut.push_back(hit ? 1u : 0u);
        if (hit) {
            ++hits;
            effect(position);
            if (spawn_items != 0 && ItemVisible(position))
                ops->spawn_item(ops->context, position, 8, -1,
                                -1.5707964f, 0.6f);
        }
        position[0] += step_x;
        position[1] += step_y;
        distance += kStep;
    } while (distance + kHalfStep <= laser->length);
    if (hits != 0)
        PreserveTrimmedRuns(laser, cut, step_x, step_y, ops);
    return hits;
}

}  // namespace

// 0x0041EFA0 - ECX is the laser this pointer; center, radius and item flag are
// the three stack arguments shown unchanged in the PE32 prologue.
int LaserCut_Circle(LaserCutState* laser, const float center[3], float radius,
                    int spawn_items, const LaserCutOps* ops) {
    return CutSamples(
        laser, spawn_items, ops,
        [center, radius](const float p[3]) { return InsideCircle(p, center, radius); },
        [laser, ops](const float p[3]) {
            float screen[3] = {p[0] + 224.0f, p[1] + 16.0f, p[2]};
            ops->spawn_spark(ops->context, screen, 17 + 2 * laser->colour);
        });
}

// 0x0041EB00 - the second vector is a full-size box, not a corner: both IDA
// and the x87 PE32 sequence multiply each component by 0.5 before forming the
// inclusive minimum/maximum bounds.
int LaserCut_Rectangle(LaserCutState* laser, const LaserCutRegion* region,
                       int spawn_items, const LaserCutOps* ops) {
    return CutSamples(
        laser, spawn_items, ops,
        [region](const float p[3]) { return InsideRectangle(p, *region); },
        [laser, ops](const float p[3]) {
            ops->spawn_spark(ops->context, p, 17 + 2 * laser->colour);
        });
}

// 0x0041DD80 - Mutable-line circular cutter.
int LaserTrim_Circle(LaserCutState* laser, const float center[3], float radius,
                     int spawn_items, const LaserCutOps* ops) {
    return TrimSamples(
        laser, spawn_items, ops,
        [center, radius](const float p[3]) {
            return InsideCircle(p, center, radius);
        },
        [laser, ops](const float p[3]) {
            float screen[3] = {p[0] + 224.0f, p[1] + 16.0f, p[2]};
            ops->spawn_spark(ops->context, screen, 17 + 2 * laser->kind);
        });
}

// 0x0041D880 - Mutable-line rectangular cutter.
int LaserTrim_Rectangle(LaserCutState* laser, const LaserCutRegion* region,
                        int spawn_items, const LaserCutOps* ops) {
    return TrimSamples(
        laser, spawn_items, ops,
        [region](const float p[3]) { return InsideRectangle(p, *region); },
        [laser, ops](const float p[3]) {
            ops->spawn_spark(ops->context, p, 17 + 2 * laser->kind);
        });
}
