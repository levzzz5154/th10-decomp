// Cluster entry: the region sweep and a synthetic caller. Retail calls the
// sweep from the enemy script interpreter, which is not C++ yet; this caller
// only gives the compiler a direct call to pick the register homes from.
#include "../../../src/game/bullet/projectile_clear_region.cpp"
#pragma code_seg(".text$f00449a00F")
extern "C" __declspec(noinline) int __stdcall ProjectileClearRegionContext(
        ProjectileManager** managers, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i)
        result += ProjectileManager_ClearRegion(managers[i], i & 1);
    return result;
}
#pragma code_seg()
