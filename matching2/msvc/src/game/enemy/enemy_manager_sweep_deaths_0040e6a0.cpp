// 0x0040E6A0: start the death bursts of the listed enemies, then tick the
// manager's clock.
#include "th10/game/enemy_death_release_0040e5f0.hpp"

struct Vector3;
void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, void** out, int index, const Vector3* position);

extern float g_frame_timer_normal_lower;  // 0x00470B68
extern float g_frame_timer_normal_upper;  // 0x00470B64

// The usual frame tick, inline. The slow step reads the speed first, which
// the volatile read pins.
static inline void TickClock(FrameTimer* clock) {
    clock->previous = clock->current;
    if (*clock->speed > g_frame_timer_normal_lower
        && *clock->speed < g_frame_timer_normal_upper) {
        ++clock->current;
        clock->elapsed += 1.0f;
    } else {
        clock->current = int(
            clock->elapsed = *(const volatile float*)clock->speed + clock->elapsed);
    }
}

#pragma code_seg(".text$079kz_sweep")
void __stdcall EnemyManager_SweepDeaths_0040e6a0(EnemyManager_0040e5f0* manager) {
    EnemyNode_0040e6a0* next;
    for (EnemyNode_0040e6a0* node = manager->first; node; node = next) {
        Enemy_0040e5f0* enemy = node->enemy;
        next = node->next;
        unsigned int flags = enemy->flags;
        if (((flags & 0x50) || (flags & 0xC000)) && !(flags & 0x80))
            continue;
        if (enemy->death_script >= 0) {
            void* burst;
            ItemAnimation_CreateOffset_00448db0(
                data_00477704->animation_files[enemy->death_file], &burst,
                enemy->death_script, (const Vector3*)&enemy->position);
        }
        enemy->flags |= 0x20000;
    }
    TickClock(&manager->clock);
}
#pragma code_seg()
