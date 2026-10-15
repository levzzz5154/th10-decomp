// 0x004067D0: spawn the projectile of one grid cell.
//
// The caller (0x004073E0) keeps the spawn blueprint in EBX and pushes the
// manager, column, row and aim angle; the register state is a native-LTCG
// convention, verified with the caller in context through the equivalent-
// recovery layout build_support/layout/equivalent/projectile_spawn_cell_004067d0.json.
// The slot scan walks the manager's 2000
// records five at a time until it finds a free one (state 0), wrapping to the
// first record whenever it steps onto one that is already leaving (state 5).
//
// The found slot is initialised from the blueprint: aim x/y from the grid
// geometry, the two frame timers, position, velocity polar, motion flags, the
// command script copy and the per-colour tables; then its command script runs
// once (0x00406D90) and the sprite's animation VM ticks (0x0043EE30). Only a
// shaped bullet (flag 2, 4 or 8) is lit at once. The
// manager's cursor advances past the slot, wrapping to the first record when
// the next one is already leaving. Returns nonzero only when the pool is full.
#include <string.h>
#include "th10/game/enemy_grid_scan_004073e0.hpp"
#include "th10/game/projectile_spawn_runtime_004067d0.hpp"
#include "th10/game/entity_script_start.hpp"
#include "th10/math/angle.hpp"
#include "th10/math/rng.hpp"

struct AnimationResourceFile;
void __stdcall Entity_StartScript(AnimationResourceFile* resource,
                                           Entity* entity, int script);
extern "C" int __stdcall RunAnimationVm(void* object);
extern "C" RngState g_rng;

// The command interpreter the spawned slot runs once (0x00406D90, recovered in
// src/game/bullet/projectile_command_runtime.cpp).
struct ProjectileCommandRuntime {
    __declspec(noinline) void Tick();
};

// A random value in [0, range), as th06's Rng::GetRandomF32InRange.
__forceinline static float Rng_RangeFloat(RngState* state, float range) {
    return Rng_NextFloat(state) * range;
}

// A shaped bullet is lit at once and steps back by one frame of its velocity.
__forceinline static void SpawnRecord_Light(ProjectileSpawnRecord* record, Vec3& position) {
    record->state = 2;
    const Vec3 shift = record->velocity * flt_4;
    position.x -= shift.x;
    position.y -= shift.y;
    position.z -= shift.z;
}

#pragma code_seg(".text$004067d0_fn")
int __stdcall SpawnPatternCell_004067d0(ProjectilePattern* pattern,
                                        ProjectileManager_004073e0* manager_view,
                                        int column, int row, float aim) {
    ProjectileSpawnManager* const manager =
        reinterpret_cast<ProjectileSpawnManager*>(manager_view);
    const ProjectileBlueprint* const blueprint =
        reinterpret_cast<const ProjectileBlueprint*>(pattern);
    ProjectileSpawnRecord* record = manager->current;
    int attempts = 0;
    for (;;) {
        if (record->state == 0)
            break;
        ++record;
        if (record->state == 5)
            record = manager->records;
        if (record->state == 0) { ++attempts; break; }
        ++record;
        if (record->state == 5)
            record = manager->records;
        if (record->state == 0) { attempts += 2; break; }
        ++record;
        if (record->state == 5)
            record = manager->records;
        if (record->state == 0) { attempts += 3; break; }
        ++record;
        if (record->state == 5)
            record = manager->records;
        if (record->state == 0) { attempts += 4; break; }
        ++record;
        if (record->state == 5)
            record = manager->records;
        attempts += 5;
        if (attempts < 2000)
            continue;
        return 1;
    }
    if (attempts >= 2000)
        return 1;

    // Grid aim: interpolate the vertical pair between rows, then place the
    // column inside the row by the layout's formula.
    float x = 0.0f;
    float y;
    if (blueprint->rows > 1) {
        const float head = blueprint->y_head;
        y = head - (head - blueprint->y_tail) * row / blueprint->rows;
    } else {
        y = blueprint->y_head;
    }
    switch (blueprint->layout) {
    case 0:
    case 1:
        if (blueprint->columns & 1) {
            x = (float)((column + 1) / 2);
        } else {
            x = (float)(column / 2) + flt_0_5;
        }
        x *= blueprint->x_spacing;
        if (column & 1)
            x *= flt_neg1;
        if (blueprint->layout == 0)
            x += aim;
        x += blueprint->x_base;
        break;
    case 2:
        x = aim;
        // fallthrough
    case 3:
        x = (float)column * flt_2pi / (float)blueprint->columns + x +
            row * blueprint->x_spacing + blueprint->x_base;
        break;
    case 4:
        x = aim;
        // fallthrough
    case 5: {
        x = x + flt_pi / (float)blueprint->columns +
            (float)column * flt_2pi / (float)blueprint->columns +
            row * blueprint->x_spacing + blueprint->x_base;
        break;
    }
    case 6:
        x = Rng_RangeFloat(&g_rng, blueprint->x_base - blueprint->x_spacing) +
            blueprint->x_spacing;
        break;
    case 7:
        y = Rng_RangeFloat(&g_rng, blueprint->y_head - blueprint->y_tail) +
            blueprint->y_tail;
        x = (float)column * flt_2pi / (float)blueprint->columns +
            row * blueprint->x_spacing + blueprint->x_base;
        break;
    case 8:
        x = Rng_RangeFloat(&g_rng, blueprint->x_base - blueprint->x_spacing) +
            blueprint->x_spacing;
        y = Rng_RangeFloat(&g_rng, blueprint->y_head - blueprint->y_tail) +
            blueprint->y_tail;
        break;
    }

    record->flags |= 1u;
    record->state = 1;
    if (!(record->timer_3f8.flags & 1u)) {
        record->timer_3f8.current = 0;
        record->timer_3f8.previous = -999999;
        record->timer_3f8.elapsed = 0.0f;
        record->timer_3f8.speed = &g_game_speed;
        record->timer_3f8.flags |= 1u;
    }
    record->timer_3f8.current = 0;
    record->timer_3f8.elapsed = 0.0f;
    record->timer_3f8.previous = -1;
    if (!(record->timer_40c.flags & 1u)) {
        record->timer_40c.current = 0;
        record->timer_40c.previous = -999999;
        record->timer_40c.elapsed = 0.0f;
        record->timer_40c.speed = &g_game_speed;
        record->timer_40c.flags |= 1u;
    }
    record->timer_40c.current = 0;
    record->timer_40c.elapsed = 0.0f;
    record->timer_40c.previous = -1;
    record->fall_speed_3d8 = y;
    record->angle_3e4 = Angle_NormalizeSum(x, 0.0f);
    Vec3& position = record->position;
    position = *reinterpret_cast<const Vec3*>(&blueprint->field_04);
    record->position.z = 0.1f;
    reinterpret_cast<ScoreGameplayPolarVector*>(&record->velocity)->SetScorePolar(x, y);
    record->motion_flags = blueprint->flags;
    record->field_7ec = blueprint->script_offset;
    record->field_7ea = blueprint->colour;
    record->flags = (record->flags & ~0xCu) | 2u;
    record->field_454 = 0;
    Entity_StartScript(
        reinterpret_cast<AnimationResourceFile*>(
            manager->animations),
        &record->sprite,
        g_bullet_script_first[blueprint->colour] + blueprint->script_offset);
    switch (g_bullet_death_selector[blueprint->colour]) {
    case 0:
        record->death_animation = blueprint->script_offset * 2 + 0x11;
        break;
    case 1:
        record->death_animation = g_bullet_death_animation[blueprint->script_offset];
        break;
    case 2:
        record->death_animation = -1;
        break;
    case 3:
        record->death_animation = 0x1D;
        break;
    case 4:
        record->death_animation = 0x13;
        break;
    }
    record->field_460 = g_bullet_field_per_colour[blueprint->colour];
    record->field_458 = blueprint->field_204;
    record->bounds_grace = 10;
    const float speed = g_bullet_speed_per_colour[blueprint->colour];
    record->height_3f4 = speed;
    record->width_3f0 = speed;
    // The stop frame follows the shape bits.
    const unsigned int shape = blueprint->flags;
    if (shape & 2u) {
        record->sprite.stop_frame = 7;
        SpawnRecord_Light(record, position);
    } else if (shape & 4u) {
        record->sprite.stop_frame = 8;
        SpawnRecord_Light(record, position);
    } else if (shape & 8u) {
        record->sprite.stop_frame = 9;
        SpawnRecord_Light(record, position);
    } else {
        record->sprite.stop_frame = 2;
    }
    memcpy(record->commands, blueprint->commands, sizeof(record->commands));
    record->field_440 = blueprint->flags;
    record->motion_flags = 0;
    record->command_index = blueprint->command_index;
    reinterpret_cast<ProjectileCommandRuntime*>(record)->Tick();
    RunAnimationVm(&record->sprite);
    // Advance the cursor past the slot, wrapping when the next one is leaving.
    ++record;
    if (record->state == 5)
        manager->current = manager->records;
    else
        manager->current = record;
    return 0;
}
#pragma code_seg()
