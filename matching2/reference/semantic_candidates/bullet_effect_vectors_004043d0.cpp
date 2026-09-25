#include "th10/game/entity.hpp"

struct BulletEffectVectors_004043d0 {
    unsigned int enabled;
    Vector3 first;
    Vector3 second;
};

// Retail 0x004043D0..0x0040440A uses EDX for the bullet and ECX/EAX for
// the two source vectors. The block begins at byte offset 0x1EEC.
extern "C" void __cdecl SetBulletEffectVectors_004043d0(
    BulletEntity* bullet, const Vector3* first, const Vector3* second) {
    BulletEffectVectors_004043d0* effect =
        reinterpret_cast<BulletEffectVectors_004043d0*>(
            reinterpret_cast<unsigned char*>(bullet) + 0x1EEC);
    effect->enabled = 1;
    effect->first.x = first->x;
    effect->first.y = first->y;
    effect->first.z = first->z;
    effect->second.x = second->x;
    effect->second.y = second->y;
    effect->second.z = second->z;
}
