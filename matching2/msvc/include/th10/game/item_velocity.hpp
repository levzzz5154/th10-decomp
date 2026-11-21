#pragma once

// 0x0041BEB0 writes the two planar components and returns their address.
// Depth remains independent: spawning clears it; the per-frame update integrates it.
struct ItemPolarVelocity2 {
    float x, y;
#ifdef TH10_ITEM_POLAR_CONTEXT_EXPORT
    TH10_ITEM_POLAR_CONTEXT_EXPORT
#endif
#ifdef _MSC_VER
    __declspec(noinline)
#else
    __attribute__((noinline))
#endif
    ItemPolarVelocity2* SetPolar(float angle, float speed);
};

struct ItemVelocity {
    ItemPolarVelocity2 xy;
    float z;
};

typedef char ItemPlanarVelocitySize[sizeof(ItemPolarVelocity2) == 8 ? 1 : -1];
typedef char ItemVelocitySize[sizeof(ItemVelocity) == 12 ? 1 : -1];
