// Compiler context only; never selected as recovered game code. Retail never
// calls CountNearPoint; this caller gives the whole-program link a direct call
// to pick the private register homes from (manager in ECX, point in EDI,
// radius on the stack).
#include "../../../src/game/bullet/projectile_point_count.cpp"

#pragma code_seg(".text$f00408400F")
extern "C" __declspec(noinline) int __stdcall ProjectilePointCountEntry(
        ProjectileManager** managers, Vec3* points, int count, float radius) {
    int result = 0;
    for (int i = 0; i < count; ++i)
        result += managers[i]->CountNearPoint(points + i, radius);
    return result;
}
#pragma code_seg()
