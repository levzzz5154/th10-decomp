// 0x004084A0: weigh the projectiles around a point. Retail never calls it.
//
// Equivalent recovery: retail writes the first two corners' y to the stack and
// reads them back for the top-right corner and the first distance, where this
// compiles to copies kept on the x87 stack. Everything else is identical.
#include "th10/game/projectile_manager.hpp"

// Squared distance on the playfield plane.
static inline float DistanceSquared(const Vec3& a, const Vec3& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// Compiler entry only: a direct caller, so the compiler picks the private
// register homes (manager in ECX, point in EDI).
extern "C" __declspec(noinline) int __stdcall ProjectilePointCountEntry(
        ProjectileManager** managers, Vec3* points, int count, float radius) {
    int result = 0;
    for (int i = 0; i < count; ++i)
        result += managers[i]->CountNearPoint(points + i, radius);
    return result;
}

int ProjectileManager::CountNearPoint(const Vec3* point, float radius) {
    float reach = radius * radius;
    int weight = 0;
    ProjectileRecord* record = records;
    int remaining = 2000;
    Vec3 corner[4];
    do {
        if (record->state != 0 && record->state != 3) {
            corner[1].x = record->position.x - record->size.x * 0.5f;
            corner[1].y = record->position.y - record->size.y * 0.5f;
            corner[0].x = record->position.x + record->size.x * 0.5f;
            corner[0].y = record->position.y + record->size.y * 0.5f;
            corner[2].x = corner[1].x;
            corner[2].y = corner[1].y;
            corner[3].x = corner[0].x;
            corner[3].y = corner[0].y;
            corner[2].y += record->size.y;
            corner[0].y -= record->size.y;

            if (DistanceSquared(*point, corner[1]) > reach &&
                DistanceSquared(*point, corner[2]) > reach &&
                DistanceSquared(*point, corner[3]) > reach &&
                DistanceSquared(*point, corner[0]) > reach) {
                continue;
            }
            if (record->sprite) {
                if (record->sprite->size <= 8.0f) ++weight;
                else if (record->sprite->size <= 16.0f) ++weight;
                else if (record->sprite->size <= 32.0f) weight += 4;
                else if (record->sprite->size <= 64.0f) weight += 10;
            }
        }
    } while (++record, --remaining);
    return weight;
}
