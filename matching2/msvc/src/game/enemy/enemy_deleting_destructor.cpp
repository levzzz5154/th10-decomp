// 0x0040CC50..0x00413170: Enemy_DeletingDestructor, PolarMotion_SetAngle
#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
void* __fastcall Enemy_DeletingDestructor(void* enemy, unsigned int unused, unsigned int flags) {
    ((EnemyDestroyFn)Enemy_ReleaseState)(enemy);
    if (flags & 1)
        operator delete(enemy);
    return enemy;
}


#include "../../../include/th10/source_views/recovery_leaves_f39a06_3.hpp"
#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "th10/source_views/recovery_leaves_f39a06_3.hpp"
struct PolarMotionAngleState {
    unsigned char pad_00[0x1C];
    float angle;
};

void PolarMotion_SetAngle(void* state, float angle) {
    static_cast<PolarMotionAngleState*>(state)->angle = Angle_Normalize(angle);
}

