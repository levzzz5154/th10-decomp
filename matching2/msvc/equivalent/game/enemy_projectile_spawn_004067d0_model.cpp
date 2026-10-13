// 0x004067D0: spawn the projectile of one grid cell.
//
// The caller (0x004073E0) keeps the spawn blueprint in EBX and pushes the
// manager, column, row and aim angle; the register state is a native-LTCG
// convention, so this body is compiled inside the projectile_spawn_runtime
// cluster together with its caller. The slot scan walks the manager's 2000
// records five at a time until it finds a free one (state 0), wrapping to the
// first record whenever it steps onto one that is already leaving (state 5).
//
// The found slot is initialised from the blueprint: aim x/y from the grid
// geometry, the two frame timers, position, velocity polar, motion flags, the
// command script copy and the per-colour tables; then its command script runs
// once (0x00406D90) and the sprite's animation VM ticks (0x0043EE30). The
// manager's cursor advances past the slot, wrapping to the first record when
// the next one is already leaving. Returns nonzero only when the pool is full.
#include <string.h>
#include "th10/game/enemy_grid_scan_004073e0.hpp"
#include "th10/game/projectile_spawn_runtime_004067d0.hpp"
#include "th10/game/entity_script_start.hpp"
#include "th10/math/angle.hpp"
#include "th10/math/rng.hpp"

struct AnimationResource_0043e710;
void __stdcall Entity_StartScript_00404f30(AnimationResource_0043e710* resource,
                                           Entity* entity, int script);
extern "C" int __stdcall RunAnimationVm(void* object);
extern "C" RngState data_004918b0;

// The command interpreter the spawned slot runs once. Defined in
// src/game/projectile_command_runtime.cpp (0x00406D90).
struct ProjectileCommandRuntime {
    __declspec(noinline) void Tick();
};

#pragma code_seg(".text$004067d0_fn")
int SpawnPatternCell_004067d0(ProjectilePattern_004073e0* pattern,
                              ProjectileManager_004073e0* manager,
                              int column, int row, float aim) {
    ProjectilePattern_004073e0* const entry_pattern =
        *reinterpret_cast<ProjectilePattern_004073e0* const*>(&pattern);
    ProjectileSpawnManager* const entry_manager =
        *reinterpret_cast<ProjectileSpawnManager* const*>(&manager);
    ProjectileSpawnRecord* record = entry_manager->current;
    ProjectileSpawnRecord* const records_base =
        reinterpret_cast<ProjectileSpawnManager*>(manager)->records;
    ProjectileBlueprint_004067d0* blueprint =
        reinterpret_cast<ProjectileBlueprint_004067d0*>(entry_pattern);
    int attempts = 0;
    for (;;) {
        if (record->state == 0)
            break;
        ++record;
        if (record->state == 5)
            record = reinterpret_cast<ProjectileSpawnManager*>(manager)->records;
        if (record->state == 0) { ++attempts; break; }
        ++record;
        if (record->state == 5)
            record = reinterpret_cast<ProjectileSpawnManager*>(manager)->records;
        if (record->state == 0) { attempts += 2; break; }
        ++record;
        if (record->state == 5)
            record = reinterpret_cast<ProjectileSpawnManager*>(manager)->records;
        if (record->state == 0) { attempts += 3; break; }
        ++record;
        if (record->state == 5)
            record = reinterpret_cast<ProjectileSpawnManager*>(manager)->records;
        if (record->state == 0) { attempts += 4; break; }
        ++record;
        if (record->state == 5)
            record = reinterpret_cast<ProjectileSpawnManager*>(manager)->records;
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
        y = blueprint->y_head -
            (blueprint->y_head - blueprint->y_tail) * row / blueprint->rows;
    } else {
        y = blueprint->y_head;
    }
    switch (blueprint->layout) {
    case 0:
    case 1:
        if (blueprint->columns & 1) {
            x = (float)((column + 1) / 2);
        } else {
            x = (float)(column / 2) + data_00470b0c;
        }
        x *= blueprint->x_spacing;
        if (column & 1)
            x *= data_00470b60;
        if (blueprint->layout == 0)
            x += aim;
        x += blueprint->x_base;
        break;
    case 2:
        x = aim;
        // fallthrough
    case 3:
        x = (float)column * data_00470b14 / (float)blueprint->columns + x +
            row * blueprint->x_spacing + blueprint->x_base;
        break;
    case 4:
        x = aim;
        // fallthrough
    case 5: {
        const float columns = (float)blueprint->columns;
        x = x + data_00470b18 / columns +
            (float)column * data_00470b14 / columns +
            row * blueprint->x_spacing + blueprint->x_base;
        break;
    }
    case 6:
        x = (blueprint->x_base - blueprint->x_spacing) * Rng_NextFloat(&data_004918b0) +
            blueprint->x_spacing;
        break;
    case 7:
        y = (blueprint->y_head - blueprint->y_tail) * Rng_NextFloat(&data_004918b0) +
            blueprint->y_tail;
        x = (float)column * data_00470b14 / (float)blueprint->columns +
            row * blueprint->x_spacing + blueprint->x_base;
        break;
    case 8:
        x = (blueprint->x_base - blueprint->x_spacing) * Rng_NextFloat(&data_004918b0) +
            blueprint->x_spacing;
        y = (blueprint->y_head - blueprint->y_tail) * Rng_NextFloat(&data_004918b0) +
            blueprint->y_tail;
        break;
    }

    record->flags |= 1u;
    record->state = 1;
    if (!(record->timer_3f8.flags & 1u)) {
        record->timer_3f8.current = 0;
        record->timer_3f8.previous = -999999;
        record->timer_3f8.elapsed = 0.0f;
        record->timer_3f8.speed = &data_00476f78;
        record->timer_3f8.flags |= 1u;
    }
    record->timer_3f8.current = 0;
    record->timer_3f8.elapsed = 0.0f;
    record->timer_3f8.previous = -1;
    if (!(record->timer_40c.flags & 1u)) {
        record->timer_40c.current = 0;
        record->timer_40c.previous = -999999;
        record->timer_40c.elapsed = 0.0f;
        record->timer_40c.speed = &data_00476f78;
        record->timer_40c.flags |= 1u;
    }
    record->timer_40c.current = 0;
    record->timer_40c.elapsed = 0.0f;
    record->timer_40c.previous = -1;
    record->fall_speed_3d8 = y;
    record->angle_3e4 = Angle_NormalizeSum(x, 0.0f);
    record->position = *reinterpret_cast<const Vec3*>(&blueprint->field_04);
    record->position.z = 0.1f;
    reinterpret_cast<ScoreGameplayPolarVector*>(&record->velocity)->SetScorePolar(x, y);
    record->motion_flags = blueprint->flags;
    record->field_7ec = blueprint->script_offset;
    record->field_7ea = blueprint->colour;
    record->flags = (record->flags & ~0xCu) | 2u;
    record->field_454 = 0;
    Entity_StartScript_00404f30(
        reinterpret_cast<AnimationResource_0043e710*>(
            reinterpret_cast<ProjectileSpawnManager* volatile>(manager)->animations),
        &record->sprite,
        data_00474170[blueprint->colour] + blueprint->script_offset);
    switch (data_004742c0[blueprint->colour]) {
    case 0:
        record->death_animation = blueprint->script_offset * 2 + 0x11;
        break;
    case 1:
        record->death_animation = data_0047432c[blueprint->script_offset];
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
    record->field_460 = data_00474250[blueprint->colour];
    record->field_458 = blueprint->field_204;
    record->bounds_grace = 10;
    const float speed = data_004741e0[blueprint->colour];
    record->height_3f4 = speed;
    record->width_3f0 = speed;
    const unsigned int shape = blueprint->flags;
    if (shape & 2u)
        record->sprite.stop_frame = 7;
    else if (shape & 4u)
        record->sprite.stop_frame = 8;
    else if (shape & 8u)
        record->sprite.stop_frame = 9;
    else
        record->sprite.stop_frame = 2;
    record->state = 2;
    const Vec3 shift = record->velocity * data_00470c40;
    record->position.x -= shift.x;
    record->position.y -= shift.y;
    record->position.z -= shift.z;
    memcpy(record->commands, blueprint->commands, sizeof(record->commands));
    record->field_440 = blueprint->flags;
    record->motion_flags = 0;
    record->command_index = blueprint->command_index;
    reinterpret_cast<ProjectileCommandRuntime*>(record)->Tick();
    RunAnimationVm(&record->sprite);
    ++record;
    ++record;
    if (record->state == 5)
        reinterpret_cast<ProjectileSpawnManager*>(manager)->current = records_base;
    else
        reinterpret_cast<ProjectileSpawnManager*>(manager)->current = record;
    return 0;
}
#pragma code_seg()

// Whole-program context: the ABI anchors whose bodies the /GL pass needs to
// derive the retail register states at the spawn path's call sites. None of
// these bytes are exported as recovered code.
#include "../../layout/ltcg/projectile_spawn_runtime/start_script.cpp"
#include "../../layout/ltcg/projectile_spawn_runtime/polar_set.cpp"
