#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
void* __fastcall Enemy_DeletingDestructor(void* enemy, unsigned int unused, unsigned int flags) {
    ((EnemyDestroyFn)asm_FUN_0040dae0_0040dae0)(enemy);
    if (flags & 1)
        operator delete(enemy);
    return enemy;
}


#include "../../../include/th10/source_views/recovery_leaves_f39a06_3.hpp"
#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "th10/source_views/recovery_leaves_f39a06_3.hpp"
void Score_SetNormalizedAngle(void* state, float angle) {
    *(float*)((unsigned char*)state + 0x1C) = Angle_Normalize(angle);
}

